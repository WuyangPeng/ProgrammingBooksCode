package com.tcre;

public interface UserDatabase
{
	User readUser(String userName);
	void writeUser(User user);
}
