/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   phonebook.cpp
/// \author Martin Reddy
/// \brief  A simple phone book API
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

#include "phonebook.h"

Person::Person()
    : mName(""),
      mHomeNumber("")
{
}

Person::Person(const std::string& name)
    : mName(name),
      mHomeNumber("")
{
}

Person::~Person()
{
}

void Person::SetName(const std::string& name)
{
    mName = name;
}

std::string Person::GetName() const
{
    return mName;
}

void Person::SetHomeNumber(const std::string& number)
{
    mHomeNumber = number;
}

std::string Person::GetHomeNumber() const
{
    return mHomeNumber;
}

Person* Person::clone() const
{
    return new Person(*this);
}

PersonWithCell* PersonWithCell::clone() const
{
    return new PersonWithCell(*this);
}

PersonWithCell::PersonWithCell()
    : mCellNumber("")
{
}

PersonWithCell::PersonWithCell(const std::string& name)
    : Person(name),
      mCellNumber("")
{
}

void PersonWithCell::SetCellNumber(const std::string& number)
{
    mCellNumber = number;
}

std::string PersonWithCell::GetCellNumber() const
{
    return mCellNumber;
}

PhoneBook::PhoneBook()
{
}

PhoneBook::~PhoneBook()
{
    PersonList::iterator it;
    for (it = mList.begin(); it != mList.end();)
    {
        Person* person = *it;
        mList.erase(it);
        delete person;
    }
}

int PhoneBook::GetSize() const
{
    return mList.size();
}

void PhoneBook::AddPerson(Person* p)
{
    mList.push_back(p->clone());
}

void PhoneBook::RemovePerson(const std::string& name)
{
    PersonList::iterator it;
    for (it = mList.begin(); it != mList.end();)
    {
        Person* person = *it;
        if (person->GetName() == name)
        {
            mList.erase(it);
            delete person;
        }
        else
        {
            ++it;
        }
    }
}

Person* PhoneBook::FindPerson(const std::string& name)
{
    PersonList::iterator it;
    for (it = mList.begin(); it != mList.end(); ++it)
    {
        Person* person = *it;
        if (person->GetName() == name)
        {
            return person;
        }
    }
    static Person empty;
    return &empty;
}

PhoneBook::PersonList::iterator PhoneBook::begin()
{
    return mList.begin();
}

PhoneBook::PersonList::iterator PhoneBook::end()
{
    return mList.end();
}
