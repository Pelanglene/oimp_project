#include "sort_students.h"
#include <algorithm>

bool operator<(const Date &a, const Date &b) {
    if (a.year < b.year) {
        return true;
    }
    if (a.year > b.year) {
        return false;
    }
    if (a.month < b.month) {
        return true;
    }
    if (a.month > b.month) {
        return false;
    }
    if (a.day < b.day) {
        return true;
    }
    if (a.day > b.day) {
        return false;
    }
    return false;
}


bool operator==(const Date &a, const Date &b) {
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

bool operator>(const Date &a, const Date &b) {
    return !(a < b || a == b);
}

bool operator!=(const Date &a, const Date &b) {
    return !(a == b);
}

bool CompareName(const Student &a, const Student &b) {
    if (a.last_name < b.last_name) {
        return true;
    }
    if (a.last_name > b.last_name) {
        return false;
    }
    if (a.name < b.name) {
        return true;
    }
    if (a.name > b.name) {
        return false;
    }
    return true;
}

bool CompareDate(const Student &a, const Student &b) {
    if (a.birth_date < b.birth_date) {
        return true;
    }
    if (a.birth_date > b.birth_date) {
        return false;
    }
    return true;
}


bool DateComp(const Student &a, const Student &b) {
    if (a.birth_date != b.birth_date) {
        return CompareDate(a, b);
    }
    return CompareName(a, b);
}

bool NameComp(const Student &a, const Student &b) {
    if (a.last_name != b.last_name || a.name != b.name) {
        return CompareName(a, b);
    }
    return CompareDate(a, b);
}

void SortStudents(std::vector<Student> &students, SortKind sortKind) {
    if (sortKind == SortKind::Name) {
        std::sort(students.begin(), students.end(), NameComp);
    } else {
        std::sort(students.begin(), students.end(), DateComp);
    }
}