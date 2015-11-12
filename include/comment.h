// Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas

#ifndef INCLUDE_COMMENT_H_
#define INCLUDE_COMMENT_H_

#include <vector>
#include <string>
#include <initializer_list>

using std::string;
using std::vector;
using std::initializer_list;

namespace ucbimp {

/**
 *  \class      Comment
 *  \brief      Represents comments for files, images and more.
 *
 *  This class manages comments composed of paragraphs.
 *
 *  \copyright  Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas
 *  \author     Axel Ohlmann, Patrick Scheid
 *  \version    0.1
 *  \date       10.11.2015
 */
class Comment {
 public:
    // Constructors and Destructor
    Comment();
    explicit Comment(string paragraph);
    explicit Comment(initializer_list<string> paragraph_list);
    Comment(const Comment &other);
    virtual ~Comment();

    // Class methods
    string remove(size_t index);
    string remove(const string &paragraph);

    void append(const string &paragraph);
    void insert(const string &paragraph, size_t index);
    void insert_before(const string &successor, const string &paragraph);
    void insert_after(const string &predecessor, const string &paragraph);

    size_t length();
    void clear();

    string &at(size_t index);
    vector<string>::const_iterator find(const string &paragraph);
    bool contains(const string &paragraph);

 private:
    vector<string> data;
};

}  // namespace ucbimp

#endif  // INCLUDE_COMMENT_H_
