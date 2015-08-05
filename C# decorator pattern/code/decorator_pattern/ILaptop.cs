using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace decorator_pattern
{
    public interface ILaptop
    {
        string GetName();
        string GetProductDetails();
        int GetPrice();
    }
}
