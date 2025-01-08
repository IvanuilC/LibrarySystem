#include <iostream>
#include <string>
#include <vector>

class Book {
protected:
    std::string title;
    std::string author;
    double price;

public:
    Book(const std::string& title, const std::string& author, double price)
        : title(title), author(author), price(price) {}

    double getPrice() const {
        return price;
    }

    std::string getTitle() const {
        return title;
    }

    void displayDetails() const {
        std::cout << "Title: " << title << ", Author: " << author << ", Price: " << price << "\n";
    }
};

class Member {
protected:
    std::string name;
    std::string memberId;

public:
    Member(const std::string& name, const std::string& memberId)
        : name(name), memberId(memberId) {}

    virtual void borrowBook(const Book& book) {
        std::cout << name << " borrowed the book: " << book.getTitle() << "\n";
    }
};

class Librarian : public Member {
public:
    Librarian(const std::string& name, const std::string& memberId)
        : Member(name, memberId) {}

    void borrowBook(const Book& book) override {
        std::cout << name << " (Librarian) borrowed the book for maintenance: " << book.getTitle() << "\n";
    }

    virtual void addBook(std::vector<Book>& catalog, const Book& book) {
        catalog.push_back(book);
        std::cout << name << " added the book: " << book.getTitle() << "\n";
    }
};

class HeadLibrarian : public Librarian {
public:
    HeadLibrarian(const std::string& name, const std::string& memberId)
        : Librarian(name, memberId) {}

    void addBook(std::vector<Book>& catalog, const Book& book) override {
        catalog.push_back(book);
        std::cout << name << " (Head Librarian) added the book: " << book.getTitle() << "\n";
    }

    void applyDiscount(Book& book, double discountPercentage) {
        double discountAmount = book.getPrice() * (discountPercentage / 100);
        std::cout << name << " applied a discount of " << discountPercentage << "% to the book: " << book.getTitle() << "\n";
    }
};

int main() {
    std::vector<Book> catalog;

    HeadLibrarian headLibrarian("Alice", "HL001");
    Librarian librarian("Bob", "L002");
    Member member("Charlie", "M003");

    Book book1("The Great Gatsby", "F. Scott Fitzgerald", 15.99);
    Book book2("1984", "George Orwell", 12.49);

    headLibrarian.addBook(catalog, book1);
    headLibrarian.addBook(catalog, book2);

    librarian.borrowBook(book1);
    member.borrowBook(book2);

    headLibrarian.applyDiscount(book1, 10);

    return 0;
}
