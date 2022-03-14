#include <iostream>


#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

int main(int argc, char **argv) {
  std::string host = "tcp://gc-gsma:3306";
  std::string user = "gcarter";
  std::string pass = "";

  std::cout << "Connection to " << host << std::endl;

  sql::Driver *driver = get_driver_instance();
  sql::Connection *con = driver->connect(host, user, pass);

  sql::Statement *stmt = con->createStatement();
  stmt->execute("USE gsma_srs");

  sql::PreparedStatement *pstmt = con->prepareStatement("SELECT id FROM mnos WHERE id=? LIMIT 10");
  pstmt->setInt(1, 6451);
  sql::ResultSet *res = pstmt->executeQuery();

  while(res->next()) {
    std::cout << "ID: " << res->getString("id") << std::endl;
  } // while

  delete res;
  delete stmt;
  delete con;
} // main
