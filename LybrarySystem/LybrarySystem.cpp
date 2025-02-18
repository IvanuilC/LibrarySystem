#include <iostream>
#include <vector>
#include <string>

// Класс Book
class Book {
protected:
    std::string title;
    std::string author;
    double price;

public:
    Book(const std::string& t, const std::string& a, double p) : title(t), author(a), price(p) {}

    double getPrice() const { return price; }
    std::string getTitle() const { return title; }

    void displayDetails() const {
        std::cout << "Title: " << title << ", Author: " << author << ", Price: " << price << std::endl;
    }

    void setDiscount(double discount) { price -= price * (discount / 100); }
};

// Класс DigitalBook (наследует Book)
class DigitalBook : public Book {
private:
    std::string url;

public:
    DigitalBook(const std::string& t, const std::string& a, double p, const std::string& u) 
        : Book(t, a, p), url(u) {}

    std::string getURL() const { return url; }
};

// Класс Member
class Member {
protected:
    std::string name;
    std::string memberId;
    std::vector<Book> borrowedBooks;

public:
    Member(const std::string& n, const std::string& id) : name(n), memberId(id) {}

    void borrowBook(Book& book) { borrowedBooks.push_back(book); }

    size_t getBorrowedCount() const { return borrowedBooks.size(); }
};

// Класс PremiumMember (наследует Member)
class PremiumMember : public Member {
private:
    int bonusPoints;

public:
    PremiumMember(const std::string& n, const std::string& id, int points) 
        : Member(n, id), bonusPoints(points) {}

    int getBonusPoints() const { return bonusPoints; }
};

// Класс Librarian
class Librarian {
protected:
    std::string name;
    std::string memberId;

public:
    Librarian(const std::string& n, const std::string& id) : name(n), memberId(id) {}

    void addBook(std::vector<Book>& catalog, const Book& book) { catalog.push_back(book); }

    bool isBookAvailable(const std::vector<Book>& catalog, const std::string& title) const {
        for (const auto& book : catalog) {
            if (book.getTitle() == title) return true;
        }
        return false;
    }
};

// Класс HeadLibrarian (усложнённый)
class HeadLibrarian : public Librarian {
private:
    std::vector<Librarian> staff;

public:
    HeadLibrarian(const std::string& n, const std::string& id) : Librarian(n, id) {}

    void applyDiscount(Book& book, double discount) { book.setDiscount(discount); }

    size_t totalBooksManaged(const std::vector<Book>& libraryCatalog) const { return libraryCatalog.size(); }

    void manageLibrarians(std::vector<Librarian>& librarians) { staff = librarians; }

    bool isBookInLibrary(const std::vector<Book>& catalog, const std::string& title) const {
        return isBookAvailable(catalog, title);
    }
};

// Класс Library
class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(Book& book) { books.push_back(book); }

    void registerMember(Member& member) { members.push_back(member); }

    bool loanBook(Member& member, const std::string& bookTitle) {
        for (auto& book : books) {
            if (book.getTitle() == bookTitle) {
                member.borrowBook(book);
                return true;
            }
        }
        return false;
    }
};

// Класс Transaction
class Transaction {
private:
    Member member;
    Book book;
    std::string date;

public:
    Transaction(const Member& m, const Book& b, const std::string& d) : member(m), book(b), date(d) {}

    void getTransactionInfo() const {
        std::cout << "Transaction: " << member.getBorrowedCount() 
                  << " books borrowed, Book: " << book.getTitle() 
                  << ", Date: " << date << std::endl;
    }
};

// Тестирование кода
int main() {
    Book book1("C++ Primer", "Lippman", 45.99);
    DigitalBook ebook("Effective C++", "Meyers", 39.99, "http://ebooks.com/effective_cpp");

    Member member("Alice", "M123");
    PremiumMember premiumMember("Bob", "P456", 100);

    Librarian librarian("John", "L001");
    HeadLibrarian headLibrarian("Sarah", "H001");


    Library library;
    library.addBook(book1);
    library.registerMember(member);

    library.loanBook(member, "C++ Primer");

    headLibrarian.applyDiscount(book1, 10);

    Transaction transaction(member, book1, "2025-02-18");
    transaction.getTransactionInfo();

    return 0;
}
