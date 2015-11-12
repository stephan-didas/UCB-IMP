// Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas

#include <comment.h>
#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::find;
using ucbimp::Comment;

/**
 * \brief   Default constructor creating empty comment.
 */
Comment::Comment() {
    // EMPTY
}

/**
 * \brief   Creates a comment containing.
 * \param   paragraph   String containing a first paragraph.
 */
Comment::Comment(string paragraph) {
    data.push_back(paragraph);
}

/**
 * \brief   Creates a comment from multiple given paragraphs.
 * \param   paragraph_list  List of multiple paragraphs to compose comment.
 */
Comment::Comment(initializer_list<string> paragraph_list) {
    for (auto par : paragraph_list) {
        data.push_back(par);
    }
}

/**
 * \brief   Copy constructor.
 * \param   other   Constant reference on comment to copy.
 */
Comment::Comment(const Comment &other) {
    data = other.data;
}

/**
 * \brief   Virtual destructor.
 */
Comment::~Comment() {
    // EMPTY
}

/**
 * \brief   Removes paragraph at given index from comment.
 * \param   index   Index of paragraph to delete.
 * \return  Copy of deleted paragraph.
 */
string Comment::remove(size_t index) {
    string copy = data.at(index);
    data.erase(begin(data) + index);
    return copy;
}

/**
 * \brief   Removes given paragraph from comment.
 * \param   paragraph   Content of paragraph to delete.
 * \return  Copy of deleted paragraph.
 */
string Comment::remove(const string &paragraph) {
    string ret = "ERROR";
    auto it = Comment::find(paragraph);
    if (it != end(data))
        ret = *it;
    data.erase(it);
    return ret;
}

/**
 * \brief   Appends new paragraph to comment.
 * \param   paragraph   New paragraph.
 */
void Comment::append(const string &paragraph) {
    data.push_back(paragraph);
}

/**
 * \brief   Inserts or overwrites new paragraph at given index.
 * \param   paragraph   New paragraph.
 * \param   index       Index representing place for new paragraph.
 */
void Comment::insert(const string &paragraph, size_t index) {
    data.insert(begin(data) + index, paragraph);
}

/**
 * \brief   Inserts a paragraph before another given paragraph.
 * \param   successor   Successor paragraph as orientation for insert.
 * \param   paragraph   New paragraph to insert.
 */
void Comment::insert_before(const string &successor, const string &paragraph) {
    auto it = Comment::find(successor);
    if (it != end(data))
        data.insert(it, paragraph);
}

/**
 * \brief   Inserts a paragraph behind another given paragraph.
 * \param   predecessor Predecessor paragraph as orientation for insert.
 * \param   paragraph   New paragraph to insert.
 */
void Comment::insert_after(const string &predecessor, const string &paragraph) {
    auto it = Comment::find(predecessor);
    if (it != end(data)) {
        data.insert(++it, paragraph);
    }
}

/**
 * \brief   Number of paragraphs the comment consists of.
 * \return  Number of paragraphs.
 */
size_t Comment::length() {
    return data.size();
}

/**
 * \brief   Deletes all already saved paragraphs.
 */
void Comment::clear() {
    data.clear();
}

/**
 * \brief   Finds paragraph in comment.
 * \param   paragraph   Paragraph to search for in given comment.
 * \return  Iterator pointing to the found paragraph or to end if not found.
 */
vector<string>::const_iterator Comment::find(const string &paragraph) {
    return std::find(begin(data), end(data), paragraph);
}

/**
 * \brief   Checks if given paragraph is contained in comment.
 * \param   paragraph   Paragraph to search for.
 * \return  Boolen variable indicating if paragraph is found (true) or not
 * (false).
 */
bool Comment::contains(const string &paragraph) {
    return (std::find(begin(data), end(data), paragraph) != end(data));
}

/**
 * \brief   Access a certain paragraph given by index.
 * \param   index   Index of the paragraph to access.
 * \return  Reference to paragraph at given index.
 * \throws  out_of_range exception when a boundary is violated.
 */
string &Comment::at(size_t index) {
    return data.at(index);
}
