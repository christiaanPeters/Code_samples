using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class GPU : LaptopDecorator
    {
        public GPU(ILaptop Laptop)
            : base(Laptop)
        {
            name = "GPU";
            price = 200;
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
