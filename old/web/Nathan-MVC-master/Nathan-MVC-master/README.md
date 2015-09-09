Nathan MVC Framework!
===

Welcome to what is probably one of the most basic PHP MVC frameworks you'll find.

The idea of Nathan MVC (I honestly couldn't think of a better name) is for PHP developers 
not necessarily versed on the basics of the Model View Controller pattern to have a framework 
clean of clutter and unnecessary addons, so they can focus on exploring the fundamentals of the 
pattern while having a working example from the very first step.

Nathan MVC comes with a .htaccess file built to allow `/controller/action/id` style URL requests, 
error and home controller and model classes which act as examples, and a basic main template file. 
There are also five classes and index.php, which form the underlying structure of the framework.

This framework is based on a series of articles I wrote for my portfolio website www.nathandavison.com, 
although it has evolved from the structure outlined in those articles.

Installation
---

Simply copy this project to a working Apache web server with PHP. It may work on other web servers, 
but the `/controller/action` URL rewriting will only work on Apache out-of-the-box.

Tested versions include Apache 2.2.3 and PHP 5.3.6.

Tips
---

- Check out how HomeController and ErrorController are coded to understand how the MVC components of this 
framework tie together - pay particular note to how they extend from BaseController, and how they 
interact with the view object i.e. `$this->view`.
- All controllers should be class files contained in the controller directory, and share the same filename 
as the controller used in the URL, with a PHP extension e.g. `controllers/home.php`. The actual class name of 
a controller should be NameController e.g. `HomeController`, `ErrorController`, etc.
- All controllers must extend from the `BaseController` class. Controllers which don't will produce an error.
- All directories under `/views` should share the name of the controller class, with an upper case first letter, 
and minus the 'Controller' part, e.g. Home, Error, etc (upper case first letter is important on Linux).
- If you want any view to be shown without using a main template, pass a boolean false as the second argument 
in the `$this->view->output()` call of your controller methods (where the first argument is the data being send 
to the view).
- If you define a string as `$this->view->output()`'s second argument, it will look for that string as 
`/views/stringvalue.php` for that view's template. "maintemplate" is the default value and hence 
`views/maintemplate.php` is the default template file.
- If you extend a model class from `BaseModel`, it will have access to the `ViewModel` object via 
`$this->viewModel`, which has a method, `set()`, that allows you to dynamically add properties to the 
`$this->viewModel` object. E.g. `$this->viewModel->set('pageTitle', 'Home')` would store the string 'Home' 
in `$this->viewModel->pageTitle`.
- In general, the framework is designed for models to extend from `BaseModel` and populate `$this->viewModel` 
with the data you want passed to the view. As such, after populating `$this->viewModel`, model methods should 
return `$this->viewModel`. However, the framework does not impose any requirements on how you handle your 
models, this is just a guideline.
- Whatever you pass as the first argument of `$this->view->output()` is available as the variable 
`$viewMode`l in templates and views. If the variable being passed in is of type `ViewModel` as talked about 
in the point above, then in your views and templates you can retrieve values using `$viewModel->get('name')`, 
where 'name' is the name of the property. For instance, in the above example where the property 'pageTitle' was set, 
retrieving this would be done as `$viewModel->get('pageTitle')`. 

Where to now
---

If you intend to expand on this framework, your first step is to probably think about where you'll store images, 
css files and js files (/content and /js ?), and to modify the `maintemplate.php` file under `/views`. From there, 
you can start creating controllers and models appropriately, making sure to extend from the base classes for each 
(see the existing home and error controllers and models for examples). Then you'll want to match your controller 
structure in the views directory, and create a view file for each of your controller's actions/methods 
(again, home and error can be used as an example).

With this all done, any controller, action and view setup you create should be viewable via `/controller/action`.

If you want to extend the capability of your models, such as including the ability for them to interact with a 
database, your best bet would be to establish your extensions in the `BaseModel` class's constructor. Since any 
model should extend from this class, they would therefore inherit any functionality you add. Other than a database 
connection, other examples include functionality for generating, validating, and sanitizing.
