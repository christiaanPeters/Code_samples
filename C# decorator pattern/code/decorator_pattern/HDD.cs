using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class HDD : LaptopDecorator
    {
        public HDD(ILaptop Laptop)
            : base(Laptop)
        {
            name = "HDD";
            price = 100;
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
