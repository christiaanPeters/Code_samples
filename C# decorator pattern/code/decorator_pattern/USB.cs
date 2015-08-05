using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    class USB : LaptopDecorator
    {
        public USB(ILaptop Laptop)
            :base(Laptop)
        {
            name = "USB hub";
            price = 10;
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
