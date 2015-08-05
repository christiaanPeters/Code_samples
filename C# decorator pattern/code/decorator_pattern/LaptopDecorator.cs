using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    abstract class LaptopDecorator : ILaptop
    {
        protected string name;
        protected int price;
        private ILaptop laptop;

        public LaptopDecorator(ILaptop Laptop)
        {
            this.laptop = Laptop;
        }

        virtual public string GetName()
        {
            return laptop.GetName();
        }
        virtual public string GetProductDetails()
        {
            return laptop.GetProductDetails();
        }

        virtual public int GetPrice()
        {
            return laptop.GetPrice();
        }
    }
}
