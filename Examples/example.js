// All members of CPerson are public by default.
class CPerson{
   var name : String;
   var address : String;

   // CPerson constuctor
   function CPerson(name : String){
      this.name = name;
   };

   // printMailingLabel is an instance method, as it uses the
   // name and address information of the instance.
   function printMailingLabel(){
      print(name);
      print(address);
   };

   // printBlankLabel is static as it does not require
   // any person-specific information.
   static function printBlankLabel(){
      print("-blank-");
   };
}

// Create an extension to CPerson.
class CCustomer extends CPerson{
   var billingAddress : String;
   var lastOrder : String;

   // Constructor for this class.
   function CCustomer(name : String, creditLimit : double){
      super(name); // Call superclass constructor.
      this.creditLimit = creditLimit;
   };

   // Customer's credit limit. This is a private field
   // so that only member functions can change it. 
   private var creditLimit : double;
   // A public property is needed to read the credit limit.
   function get CreditLimit() : double{
      return creditLimit;
   }
}

// Create a new CCustomer.
var Jane : CCustomer = new CCustomer("Jane Doe",500.);
// Do something with it.
Jane.billingAddress = Jane.address = "12 Oak Street, Buffalo, NY 14201";
Jane.lastOrder = "Windows 2000 Server";
// Print the credit limit.
print(Jane.name + "'s credit limit is " + Jane.CreditLimit);
// Call a method defined in the base class.
Jane.printMailingLabel();