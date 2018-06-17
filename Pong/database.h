#pragma once

#include <jdbc/mysql_driver.h>

class Database
{
	private:
		
		std::string table = "highscores";

		sql::Driver *driver;

	public:
		Database();
		void addScore(std::string name, int score);

	private:
		std::string getCurrentDate();
		std::string getCurrentTime();
};