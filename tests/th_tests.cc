#include <gtest/gtest.h>
#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <my_tests.hpp>
#include <my_book_factory.hpp>

// Demonstrate some basic assertions.

TEST(thTest, test01_txt)
{
    int fd = open("GoogleTestLog.log", O_WRONLY|O_CREAT|O_TRUNC, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);
    std::cout << "\n\nStream has been redirected!\n" << std::endl;
    printf("test log on file01:\n");
    EXPECT_EQ(test_file("../tests/test01.txt"), EXIT_SUCCESS);
    printf("End of test01 \n\n\n");
    close(fd);
}
TEST(thTest, test02_txt)
{
    int fd = open("GoogleTestLog.log", O_WRONLY|O_APPEND, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);
    std::cout << "\n\nStream has been redirected!\n" << std::endl;
    printf("test log on file02:\n");
    EXPECT_EQ(test_file("../tests/test02.txt"), EXIT_SUCCESS);
    printf("End of test02 \n\n\n");
    close(fd);
}

TEST(thTest, wrong_txt)
{
    int fd = open("GoogleTestLog.log", O_WRONLY|O_APPEND, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);
    std::cout << "\n\nStream has been redirected!\n" << std::endl;
    printf("test log on file01:\n");
    EXPECT_EQ(test_file("wrong.txt"), EXIT_FAILURE);
    printf("End of wrong.txt test\n\n\n");
    close(fd);
}


TEST(thTest, factory)
{
    int fd = open("GoogleTestLog.log", O_WRONLY|O_APPEND, 0660);
    assert(fd >= 0);
    int ret = dup2(fd, 1);
    assert(ret >= 0);
    std::cout << "\n\nStream has been redirected!\n" << std::endl;
    printf("test log on factory:\n");
    
    std::unique_ptr<BookCreator> creator;
    creator = std::make_unique<BandeDessineCreator>();
    std::unique_ptr<LibraryItem> item1 = creator->createBook("Lanfeust de Troy", "Christophe Arleston", "Didier Tarquin,");

    creator = std::make_unique<LivreCreator>();
    std::unique_ptr<LibraryItem> item2 = creator->createBook("Bel-Ami", "Maupassant", "", 267);

    item1->checkOut();
    item1->checkIn();

    item2->checkOut();
    item2->checkIn();

    Library myLibrary;
    myLibrary.addItem(std::move(item1));
    myLibrary.addItem(std::move(item2));
    myLibrary.displayItems();
    std::cout << "Finding title by author:" << std::endl;
    myLibrary.findBooksByAuthor("Maupassant");

    std::cout << "Runnning GOOGLE EQ:" << std::endl;
    std::vector<std::string> vec = myLibrary.returnBooksByAuthor("Maupassant");
    std::string bookTitle = vec[0];
    EXPECT_EQ(_my_strcmp(bookTitle.c_str(), "Bel-Ami"), 0);
    
    std::cout << "Finding author by title:" << std::endl;
    myLibrary.findAuthorByBookTitle("Lanfeust de Troy");

    std::cout << "Runnning GOOGLE EQ:" << std::endl;
    std::string author = myLibrary.returnAuthorByBookTitle("Lanfeust de Troy");
    EXPECT_EQ(_my_strcmp(author.c_str(), "Christophe Arleston"), 0);

    myLibrary.addAuthor("the author");
    myLibrary.addAuthor("the other author");
    myLibrary.addAuthor("the otter author");
    myLibrary.addAuthor("the other otter author");
    myLibrary.displayAuthors();

    myLibrary.removeItem("Lanfeust de Troy", "Christophe Arleston");
    myLibrary.displayItems();
    
    myLibrary.removeAuthor("the other otter author");
    myLibrary.displayAuthors();
    
    printf("End of factory test \n\n\n");
    close(fd);
}
