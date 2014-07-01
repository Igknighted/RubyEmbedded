#include <iostream>
#include <ruby.h>

using namespace std;

// This will make the compiler stop complaining when we use rb_define_method
typedef VALUE (ruby_method)(...);

// This variable is going to store the class data for our module.
VALUE example_class_name;

// This is going to be our first module method
VALUE example_method1(){
	cout << "We did it!" << endl;
	return 0;
}

int main(int argc, char **argv)
{
	int status;

	// Initiate ruby
	ruby_sysinit(&argc, &argv);
	RUBY_INIT_STACK;
	ruby_init();
	ruby_init_loadpath();


	// Create a class called Example_class on the ruby C object. (Name must start with upper case)
	example_class_name = rb_define_class("Example_class", rb_cObject);

	// This adds a method to "Example_class" called "SimpleMethod" that runs example_method1 with 0 args
	rb_define_method(example_class_name, "SimpleMethod", (ruby_method*) &example_method1, 0);


	// Execute test.rb
	rb_load_protect(rb_str_new2("./test.rb"), 0, &status);


	if (status) {
		VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
		cerr << StringValuePtr(rbError) << endl;
	};

	ruby_finalize();

	return status;

}
