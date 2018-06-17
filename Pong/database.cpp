#include "stdafx.h"
#include "database.h"

#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>

#include <iostream>
#include <sstream>
#include <exception>
#include <chrono>
#include <iomanip>
#include <ctime>

Database::Database()
{
	try
	{
		driver = sql::mysql::get_driver_instance();
	}
	catch (sql::SQLException &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

void Database::addScore(std::string name, int score)
{
	std::cerr << "Score uploaded" << std::endl;

	try
	{
		boost::scoped_ptr<sql::Connection> connection(driver->connect(host, user, password));

		if (!connection->isValid())
		{
			std::cerr << "Invalid connection" << std::endl;
			return;
		}

		connection->setSchema(database);
		boost::scoped_ptr<sql::Statement> statement(connection->createStatement());

		std::string query = "INSERT INTO `highscores`(`Name`, `Highscore`, `Date`, `Time`) "
			"VALUES (\'" + name + "\', \'" +
			std::to_string(score) + "\', \'" +
			getCurrentDate() + "\', \'" +
			getCurrentTime() + "\')\n";
		
		statement->executeQuery(query);

	}
	catch (sql::SQLException &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}

std::string Database::getCurrentDate()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::ostringstream strStream;
	strStream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");

	return strStream.str();
}

std::string Database::getCurrentTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::ostringstream strStream;
	strStream << std::put_time(std::localtime(&in_time_t), "%X");

	return strStream.str();
}