#include <iostream>
#include <memory> 
#include <vector>
#include <set>
#include <string>

// FACTORY METHOD DESIGN PATTERN WITH RAII
// per recommandation : Avoid overuse of new and destroy by making use of smart pointers and RAII principles 

class LibraryItem
{
    public:
        LibraryItem()
        {
            std::cout << "LibraryItem Created" << std::endl;
        }
        virtual void checkOut() = 0;
        virtual void checkIn() = 0;
        virtual void display() = 0;
        virtual std::string getTitle() const = 0;
        virtual std::string getAuthor() const = 0;
        virtual ~LibraryItem()
        {
            std::cout << "LibraryItem destroyed" << std::endl;
        }
};

class Livre : public LibraryItem
{
    private:
        std::string title;
        std::string author;
        int pages;
    public:
        Livre(const std::string& title, const std::string& author, int pages) 
        : title(title), author(author), pages(pages)
        {
            std::cout << "Livre Created" << std::endl;
        }

        void checkOut() override
        {
            std::cout << "Livre checkOut" << std::endl;
        }

        void checkIn() override
        {
            std::cout << "Livre checkIn" << std::endl;
        }

        void display() override
        {
            std::cout << "Title: " << title << ", Author: " << author << ", Pages: " << pages << std::endl;
        }

        std::string getTitle() const override
        {
            return title;
        }

        std::string getAuthor() const override
        {
            return author;
        }
};

class BandeDessine : public LibraryItem
{
    public:
        std::string title;
        std::string author;
        std::string illustrator;
        BandeDessine(const std::string& title, const std::string& author, const std::string& illustrator)
        : title(title), author(author), illustrator(illustrator)
        {
            std::cout << "BandeDessine Created" << std::endl;
        }

        void checkOut() override
        {
            std::cout << "BandeDessine checkOut" << std::endl;
        }

        void checkIn() override
        {
            std::cout << "BandeDessine checkIn" << std::endl;
        }

        void display() override
        {
            std::cout << "Title: " << title << ", Author: " << author << ", Illustrator: " << illustrator << std::endl;
        }

        std::string getTitle() const override
        {
            return title;
        }
        
        std::string getAuthor() const override
        {
            return author;
        }
};

// run-time polymorphism

class BookCreator
{
    public:
        virtual std::unique_ptr<LibraryItem> factoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) = 0;
        virtual ~BookCreator() {}

        std::unique_ptr<LibraryItem> createBook(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0)
        {
            std::unique_ptr<LibraryItem> smart_ptr = this->factoryMethod(title, author, illustrator, pages);
            return smart_ptr;
        }
};

class BandeDessineCreator : public BookCreator
{
    std::unique_ptr<LibraryItem> factoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) override
    {
        return std::make_unique<BandeDessine>(title, author, illustrator);
    }
};

class LivreCreator : public BookCreator
{
    std::unique_ptr<LibraryItem> factoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) override
    {
        return std::make_unique<Livre>(title, author, pages);
    }
};



class Library
{
private:
    std::vector<std::unique_ptr<LibraryItem>> items;
    std::set<std::string> authors;

public:
    void addItem(std::unique_ptr<LibraryItem> item)
    {
        const std::string& author = item->getAuthor();
        addAuthor(author);
        items.emplace_back(std::move(item));
    }

    void displayItems() const
    {
        for (const auto& item : items)
        {
            item->display();
        }
    }

    void findBooksByAuthor(const std::string& author) const
    {
        bool found = false;
        for (const auto& item : items)
        {
            if (item->getAuthor() == author)
            {
                item->display();
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "Author has no books referenced in library: " << author << std::endl;
        }
    }

    void findAuthorByBookTitle(const std::string& title) const
    {
        bool found = false;
        for (const auto& item : items)
        {
            if (item->getTitle() == title)
            {
                std::cout << "Author of \"" << title << "\" is " << item->getAuthor() << std::endl;
                found = true;
            }
        }
        if (!found)
        {
            std::cout << "No author found for the book titled: " << title << std::endl;
        }
    }

    bool addAuthor(const std::string& author)
    {
        bool result = authors.insert(author).second;
        if (result)
        {
            std::cout << "Author succesfuly added" << std::endl;
        }
        else
        {
            std::cout << "Author already exist" << std::endl;
        }
        return result;
    }

    void displayAuthors() const
    {
        for (const std::string& author : authors)
        {
            std::cout << author << std::endl;
        }
    }
};



// int main()
// {
//     std::unique_ptr<BookCreator> creator;
//     creator = std::make_unique<BandeDessineCreator>();
//     std::unique_ptr<LibraryItem> item1 = creator->createBook("Lanfeust de Troy", "Christophe Arleston", "Didier Tarquin,");

//     creator = std::make_unique<LivreCreator>();
//     std::unique_ptr<LibraryItem> item2 = creator->createBook("Bel-Ami", "Maupassant", "", 267);

//     item1->checkOut();
//     item1->checkIn();

//     item2->checkOut();
//     item2->checkIn();

//     Library myLibrary;
//     // myLibrary = std::make_unique<Library>();
//     myLibrary.addItem(std::move(item1));
//     myLibrary.addItem(std::move(item2));
//     myLibrary.displayItems();
//     std::cout << "Finding title by author:" << std::endl;
//     myLibrary.findBooksByAuthor("Maupassant");
//     std::cout << "Finding author by title:" << std::endl;
//     myLibrary.findAuthorByBookTitle("Lanfeust de Troy");
//     myLibrary.addAuthor("the author");
//     myLibrary.addAuthor("the other author");
//     myLibrary.addAuthor("the otter author");
//     myLibrary.addAuthor("the other otter author");
//     myLibrary.displayAuthors();
//     return 0;
// }