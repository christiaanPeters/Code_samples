using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class TravelLaptop : ILaptop
    {
        private string name;
        private int price;

        public TravelLaptop()
        {
            name = "Travel laptop";
            price = 500;
        }

        public string GetName()
        {
            return name;
        }

        public string GetProductDetails()
        {
            return name;
        }

        public int GetPrice()
        {
            return price;
        }
    }
}
