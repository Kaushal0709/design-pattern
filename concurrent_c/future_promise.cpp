#include<iostream>
#include<future>
#include<thread>
#include<chrono>
using namespace std;
int factorial(std::future<int>& f) {
	int x= 1;
	int N = f.get();
	for (int i = N; i > 1; i--) {
		x *= i;
	}
	//res = x;
	//cout << res << endl;
	return x;
}
int main() {
	std::promise<int> p;
	std::future<int> f = p.get_future();
	future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, std::ref(f));
	// std::launch::async will create new thread once async is called and 
	// std::launch::deffered flag will not create a thread.
	// default opetions( implementaion dependent), if not mentioned anything. std::launch::async| std::launch::deferred 
	//cout << fu.get() << endl; //if deffered is set as flag then once get method got invoked, factorial method will
	// invoked in the same thread.

	// promise will used to send the package to the child thread later in the future.
	std::this_thread::sleep_for(chrono::milliseconds(20));
	p.set_value(4);
	cout << fu.get() << endl;
	return 0;
}