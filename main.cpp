#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> 

using namespace std;

class EBook {
public:
    const int MAX_USERS_COUNT = 100000;
    const int MAX_PAGES_COUNT = 1000;

public:

    EBook()
        : total_users_count_{ 0 }
        , last_user_pages_(MAX_USERS_COUNT, 0)
        , read_page_user_counts_(MAX_PAGES_COUNT, 0) {
    }

    void AddPageReadByUser(int user, int page) {
        int last_user_page = last_user_pages_[user];
        if (last_user_page == 0) {
            ++total_users_count_;
        }
        last_user_pages_[user] = page;
        for (size_t page_ix = last_user_page + 1; page_ix <= page; ++page_ix) {
            ++read_page_user_counts_[page_ix];
        }
    }

    double GetCheerForUser(int user) {
        int last_user_page = last_user_pages_[user];
        if (last_user_page > 0) {
            int other_read_page_user_count = read_page_user_counts_[last_user_page] - 1;
            int other_total_users_count = total_users_count_ - 1;
            if (other_read_page_user_count > 0) {
                return static_cast<double>(other_total_users_count - other_read_page_user_count) / other_total_users_count;
            }
            return 1.0;
        }
        return .0;
    }

private:
    int total_users_count_;
    vector<int> last_user_pages_;
    vector<int> read_page_user_counts_;
};

void ReadInputAndHandle(istream& is, EBook& ebook, ostream& os) {
    int count = 0;
    is >> count >> std::ws;
    os << setprecision(6);

    for (int i = 0; i < count; i++)
    {
        string command;

        is >> command;
        if (command == "READ") {
            int user = 0;
            is >> user;
            int page = 0;
            is >> page;
            ebook.AddPageReadByUser(user, page);
        }
        else if (command == "CHEER") {
            int user = 0;
            is >> user;
            os << ebook.GetCheerForUser(user) << endl;
        }
    }
}

int main()
{
    EBook ebook;
    ReadInputAndHandle(cin, ebook, cout);
    return 0;
}
