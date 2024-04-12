#include <iostream>
#include <memory> 


// FACTORY METHOD DESIGN PATTERN WITH RAII
// per recommandation : Avoid overuse of new and destroy by making use of smart pointers and RAII principles 

class LibraryItem
{
    public:
        LibraryItem()
        {
            std::cout << "LibraryItem Created" << std::endl;
        }
        virtual void CheckOut() = 0;
        virtual void CheckIn() = 0;
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
        void CheckOut() override
        {
            std::cout << "Livre CheckOut" << std::endl;
        }
        void CheckIn() override
        {
            std::cout << "Livre CheckIn" << std::endl;
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
        void CheckOut() override
        {
            std::cout << "BandeDessine CheckOut" << std::endl;
        }
        void CheckIn() override
        {
            std::cout << "BandeDessine CheckIn" << std::endl;
        }
};

// run-time polymorphism

class BookCreator
{
    public:
        virtual std::unique_ptr<LibraryItem> FactoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) = 0;
        virtual ~BookCreator() {}

        std::unique_ptr<LibraryItem> CreateBook(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0)
        {
            std::unique_ptr<LibraryItem> smart_ptr = this->FactoryMethod(title, author, illustrator, pages);
            return smart_ptr;
        }
};

class BandeDessineCreator : public BookCreator
{
    std::unique_ptr<LibraryItem> FactoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) override
    {
        return std::make_unique<BandeDessine>(title, author, illustrator);
    }
};

class LivreCreator : public BookCreator
{
    std::unique_ptr<LibraryItem> FactoryMethod(const std::string& title, const std::string& author, const std::string& illustrator = "", int pages = 0) override
    {
        return std::make_unique<Livre>(title, author, pages);
    }
};

// int main()
// {
//     std::unique_ptr<BookCreator> creator;
//     creator = std::make_unique<BandeDessineCreator>();
//     std::unique_ptr<LibraryItem> item1 = creator->CreateBook("Lanfeust de Troy", "Christophe Arleston,", "Didier Tarquin,");

//     creator = std::make_unique<LivreCreator>();
//     std::unique_ptr<LibraryItem> item2 = creator->CreateBook("Bel-Ami", "Maupassant", "", 267);

//     item1->CheckOut();
//     item1->CheckIn();

//     item2->CheckOut();
//     item2->CheckIn();

//     return 0;
// }