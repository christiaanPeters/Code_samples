using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class GamingLaptop : ILaptop
    {
        private string name;
        private int price;

        public GamingLaptop()
        {
            name = "Gaming laptop";
            price = 1000;
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
