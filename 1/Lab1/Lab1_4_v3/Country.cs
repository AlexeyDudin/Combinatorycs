using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Lab1_4_v3
{
    public class City: IComparable
    {
        private bool isVisited = false;
        public string Name { get; set; }
        public bool IsVisited { get => isVisited; set => isVisited = value; }

        public int CompareTo(object city)
        {
            return Name.CompareTo(((City)city).Name);
        }
    }
    public class Path
    {
        public City From { get; set; }
        public City Dest { get; set; }
        public int Length { get; set; }
    }

    public class FindedPaths: IComparable<FindedPaths>
    {
        private List<Path> paths;
        private long length = 0;
        public List<Path> Paths 
        { 
            get => paths;
            set
            {
                paths = value;
                length = 0;
                foreach (Path path in paths)
                {
                    length += path.Length;
                }
            }
        }
        public long Lenght { get => length; }

        public int CompareTo(FindedPaths other)
        {
            if (other == null)
                return 1;

            else
                return this.Lenght.CompareTo(other.Lenght);
        }
    }

    public class Country
    {
        private City capital;
        private List<City> citys = new List<City>();
        private List<Path> paths = new List<Path>();

        public City Capital { get => capital; set => capital = value; }
        public List<City> Citys { get => citys; set => citys = value; }
        public List<Path> Paths { get => paths; set => paths = value; }

        public void PrintAllPaths()
        {
            foreach (var path in Paths) 
            {
                Console.WriteLine($"{path.From.Name} -({path.Length})-> {path.Dest.Name}");
            }
        }

        private List<Path> GetPathsFromCity(City city)
        {
            return new List<Path>(this.Paths.Where(p => p.From == city && !p.Dest.IsVisited));
        }

        private Path GetPathFromCity(City sourceCity, City destCity)
        {
            return this.Paths.Where(p => p.From == sourceCity && p.Dest == destCity).SingleOrDefault();
        }

        private List<List<Path>> RecourciveFindPath(City from, City dest)
        {
            List<List<Path>> result = new List<List<Path>>();

            List<Path> paths = GetPathsFromCity(from);
            foreach (var path in paths) 
            {
                if (dest == path.Dest)
                {
                    List<Path> tmp = new List<Path>();
                    tmp.Add(path);
                    result.Add(tmp);
                }
                else
                {
                    path.Dest.IsVisited = true;
                    var findedPaths = RecourciveFindPath(path.Dest, dest);
                    if (findedPaths.Any())
                    {
                        foreach (var elem in findedPaths)
                        {
                            List<Path> tmp = new List<Path>();
                            tmp.Add(path);
                            tmp.AddRange(elem);
                            result.Add(tmp);
                        }
                    }
                    path.Dest.IsVisited = false;
                }
            }
            return result;
        }

        private void PrintPaths(List<FindedPaths> paths)
        {
            foreach (var path in paths)
            {
                Console.Write(path.Lenght + ":");
                if (path.Paths.Count > 0)
                {
                    Console.Write(path.Paths.First().From.Name);
                    foreach (var elem in path.Paths)
                    {
                        Console.Write($"-({elem.Length})->{elem.Dest.Name}");
                    }
                }
                Console.WriteLine();
            }
        }

        private void PrintOnlyFirstPath(List<FindedPaths> paths)
        {
            Console.Write($"Из {paths.First().Paths.First().From.Name} в {paths.First().Paths.Last().Dest.Name} минимальная длина пути = ");
            Console.Write(paths.First().Lenght + ": ");
            if (paths.First().Paths.Count > 0)
            {
                Console.Write(paths.First().Paths.First().From.Name);
                foreach (var elem in paths.First().Paths)
                {
                    Console.Write($"-({elem.Length})->{elem.Dest.Name}");
                }
            }
            Console.WriteLine();
        }

        private void PrintOnlyFirstPath(FindedPaths paths)
        {
            Console.Write(paths.Paths.First().From.Name);
            foreach (var elem in paths.Paths)
            {
                Console.Write($"-({elem.Length})->{elem.Dest.Name}");
            }
            Console.WriteLine();
        }

        public void PrintPathsToCityes()
        {
            foreach (City city in Citys)
            {
                var findedPaths = RecourciveFindPath(Capital, city);
                List<FindedPaths> findedPathsList = new List<FindedPaths>();
                foreach (var pathList in findedPaths)
                {
                    FindedPaths paths = new FindedPaths();
                    paths.Paths = pathList;
                    findedPathsList.Add(paths);
                }
                findedPathsList.Sort();
                //Sort(ref findedPathsList);
                PrintOnlyFirstPath(findedPathsList);
                //PrintPaths(findedPathsList);
            }
        }

        private bool NextPermutation<T>(IList<T> a) where T : IComparable
        {
            if (a.Count < 2) return false;
            var k = a.Count - 2;

            while (k >= 0 && a[k].CompareTo(a[k + 1]) >= 0) k--;
            if (k < 0) return false;

            var l = a.Count - 1;
            while (l > k && a[l].CompareTo(a[k]) <= 0) l--;

            var tmp = a[k];
            a[k] = a[l];
            a[l] = tmp;

            var i = k + 1;
            var j = a.Count - 1;
            while (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                i++;
                j--;
            }

            return true;
        }

        public void FindComyvoyeger()
        {
            List<City> cityList = new List<City>();
            foreach (var city in citys)
            {
                cityList.Add(city);
            }
            FindedPaths result = null;
            do
            {
                FindedPaths findedPaths = new FindedPaths();
                List<Path> paths = new List<Path>();
                City prevCity = null;
                foreach (var city in cityList)
                {
                    if (prevCity != null)
                    {
                        var path = GetPathFromCity(prevCity, city);
                        if (path != null)
                        {
                            paths.Add(path);
                        }
                    }
                    prevCity = city;
                }

                findedPaths.Paths = paths;
                if (result == null || result.Lenght > findedPaths.Lenght)
                {
                    result = findedPaths;
                }
                //PrintOnlyFirstPath(findedPaths);
            } while (NextPermutation(cityList));

            PrintOnlyFirstPath(result);
        }
    }
}
