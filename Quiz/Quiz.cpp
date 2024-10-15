/*Popular restaurant Criminal Seafood does not take reservations,
but maintains a wait list where
customers who have been on the wait list longer are seated earlier.
Sometimes customers decide to
eat somewhere else, so the restaurant must remove them from the wait list.

Assume each customer
has a different name, and no two customers are added to the wait list at the exact same time.

Design
a database to help Criminal Seafood maintain its wait list supporting the following operations, each
in O(1) time. State whether each operation's running time is worst-case, amortized, and/or expected.
build(): initialize an empty database
add_name(x): add name x to the back of the wait list
remove_name(x): remove name x from the wait list
seat(): remove and return the name of the customer from the front of the wait list*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <random>
#include <chrono>

// Class to manage the waitlist
class Waitlist
{
public:
	// Adds a customer to the back of the waitlist
	void add_name(const std::string &name)
	{
		if (name_map.find(name) != name_map.end())
		{
			std::cout << "Customer already on the waitlist.\n";
			return;
		}
		// Add customer to list and map
		waitlist.push_back(name);
		name_map[name] = --waitlist.end(); // store iterator for O(1) removal
	}

	// Removes a customer from the waitlist
	void remove_name(const std::string &name)
	{
		if (name_map.find(name) == name_map.end())
		{
			std::cout << "Customer not found in the waitlist.\n";
			return;
		}
		// Remove customer from list and map
		waitlist.erase(name_map[name]);
		name_map.erase(name);
	}

	// Seats (removes) the first customer in line
	std::string seat()
	{
		if (waitlist.empty())
		{
			return "No customers to seat.";
		}
		std::string name = waitlist.front();
		waitlist.pop_front();
		name_map.erase(name);
		return name + " has been seated.";
	}

	// Prints the current state of the waitlist
	void print_waitlist()
	{
		if (waitlist.empty())
		{
			std::cout << "The waitlist is empty.\n";
			return;
		}
		std::cout << "Current Waitlist:\n";
		for (const auto &name : waitlist)
		{
			std::cout << name << " ";
		}
		std::cout << std::endl;
	}

private:
	std::list<std::string> waitlist;											// Doubly linked list for O(1) add at the back, remove from front
	std::unordered_map<std::string, std::list<std::string>::iterator> name_map; // Hash map for O(1) lookup and remove
};

// Helper function to generate random names
std::string generate_random_name(int length)
{
	const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string name;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> dist(0, characters.size() - 1);
	for (int i = 0; i < length; ++i)
	{
		name += characters[dist(generator)];
	}
	return name;
}

// Random test generator for adding and removing customers
void generate_random_test_cases(Waitlist &wl, int add_count, int remove_count)
{
	for (int i = 0; i < add_count; ++i)
	{
		std::string name = generate_random_name(5);
		std::cout << "Adding: " << name << std::endl;
		wl.add_name(name);
	}
	wl.print_waitlist();

	// Randomly removing customers
	for (int i = 0; i < remove_count; ++i)
	{
		std::string name = generate_random_name(5); // Simulate random names for testing
		std::cout << "Removing: " << name << std::endl;
		wl.remove_name(name);
	}
	wl.print_waitlist();
}

int main()
{
	Waitlist wl;

	// Dummy test cases for starting
	wl.add_name("Alice");
	wl.add_name("Bob");
	wl.add_name("Charlie");
	wl.print_waitlist();

	std::cout << wl.seat() << std::endl;
	wl.print_waitlist();

	std::cout << wl.seat() << std::endl;
	wl.print_waitlist();

	wl.add_name("Dave");
	wl.remove_name("Charlie"); // Try removing someone who was already seated
	wl.print_waitlist();

	// Now let's add random tests
	std::cout << "\nRandom Test Cases:\n";
	generate_random_test_cases(wl, 5, 3);

	return 0;
}
