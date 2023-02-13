using System;
using System.IO;
using System.Linq;

namespace Lab1_4_v2
{
    public class FileWorker
    {
        public Country ReadFromFile(string fileName)
        {
            Country country = new Country();
            string[] lines = File.ReadAllLines(fileName);
            for (int i = 0; i < lines.Length; i++)
            {
                City city = new City() { Name = i.ToString()};
                if (country.Capital == null)
                    country.Capital = city;
                country.Citys.Add(city);
            }

            int sourceCityId = 0;
            foreach (string line in lines)
            {
                int destCityId = 0;
                string[] weightString = line.Split(' ');
                foreach(string weight in weightString)
                {
                    int value = Int32.Parse(weight);
                    if (value != 0)
                    {
                        City fromCity = country.Citys.Where(c => c.Name == sourceCityId.ToString()).Single();
                        City destCity = country.Citys.Where(c => c.Name == destCityId.ToString()).Single();
                        country.Paths.Add(new Path() { From = fromCity, Dest = destCity, Length = value });
                    }
                    destCityId++;
                }
                sourceCityId++;
            }

            return country;
        }
    }
}
