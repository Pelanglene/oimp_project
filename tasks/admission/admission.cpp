#include "admission.h"
#include "algorithm"
#include <iostream>

bool operator<(Date a, Date b) {
    if (a.year < b.year) {
        return true;
    } else if (a.year > b.year) {
        return false;
    }
    if (a.month < b.month) {
        return true;
    } else if (a.month > b.month) {
        return false;
    }
    if (a.day < b.day) {
        return true;
    }
    return false;
}

bool FUCK(const Student* a, const Student* b) {
    if (a->name < b->name) {
        return true;
    } else if (a->name > b->name) {
        return false;
    }
    return a->birth_date < b->birth_date;
}

bool IsSmallerApplication(const Applicant* a, const Applicant* b) {
    if (a->points > b->points) {
        return true;
    } else if (a->points < b->points) {
        return false;
    }
    if (a->student.birth_date < b->student.birth_date) {
        return true;
    } else if (b->student.birth_date < a->student.birth_date) {
        return false;
    }
    if (a->student.name < b->student.name) {
        return true;
    }
    return false;
}

University FindUniversity(const std::string& university_name, const std::vector<University>& universities) {
    for (University un : universities) {
        if (un.name == university_name) {
            return un;
        }
    }
    return University();
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicants_copies;
    for (const Applicant& applicant : applicants) {
        applicants_copies.push_back(&applicant);
    }

    AdmissionTable student_list;

    std::sort(applicants_copies.begin(), applicants_copies.end(), IsSmallerApplication);

    for (size_t i = 0; i < applicants_copies.size(); ++i) {
        for (std::string university_name : applicants_copies[i]->wish_list) {
            University students_university = FindUniversity(university_name, universities);
            if (students_university.max_students > student_list[university_name].size()) {
                student_list[university_name].push_back(&(applicants_copies[i]->student));
                break;
            }
        }
    }

    for (University university : universities) {
        std::sort(student_list[university.name].begin(), student_list[university.name].end(), FUCK);
    }

    return student_list;
}