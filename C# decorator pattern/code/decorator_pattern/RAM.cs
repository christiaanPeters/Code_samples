using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class RAM : LaptopDecorator
    {
        public RAM(ILaptop Laptop)
            :base(Laptop)
        {
            name = "RAM";
            price = 50;
        }

        public override string GetProductDetails()
        {
            return base.GetProductDetails() + " \n" + name;
        }

        public override int GetPrice()
        {
            return price + base.GetPrice();
        }
    }
}
