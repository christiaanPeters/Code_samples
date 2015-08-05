this C# application is meant to show how a decorator pattern works.

The decorator pattern is meant to prevent class explosions.
In this example we have a "store" where laptops are sold,
the "customer" (the one controlling the application) can decide for himself what parts he wants in his laptop.
if you would have to create an entire new class for every different kind of laptop the customer comes up with, you'll quickly end up with hundreds of classes.
By using the decorator pattern, you have a base class for the laptop, which you can expand by adding a decorator class.

Every decorator class has a reference to the underlying class, so that you can still call the functions of the base class. (see "decorator pattern visualized).
 
The C# application is a simple application that uses the decorator pattern.
You can "buy" a laptop and decide for yourself what parts you want to add.
After clicking on "purchase" you can decide to create a new one, remove the selected laptop out of the list or edit the selected laptop in the list.
It'll show the price of the selected laptop and what parts have been selected for the laptop.