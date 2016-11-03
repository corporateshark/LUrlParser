#include <gtest/gtest.h>
#include "../LUrlParser.h"

using LUrlParser::clParseURL;


class UrlTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

  }
};

TEST_F(UrlTest, example) {

  clParseURL URL = clParseURL::ParseURL( "https://John:Dow@github.com:80/corporateshark/LUrlParser" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("https", URL.m_Scheme);
  ASSERT_EQ("github.com", URL.m_Host);
  ASSERT_EQ("80", URL.m_Port);
  ASSERT_EQ("corporateshark/LUrlParser", URL.m_Path);
  ASSERT_EQ("", URL.m_Query);
}

TEST_F(UrlTest, cases) {

  clParseURL URL = clParseURL::ParseURL( "HTTPS://ESPN.com/BOLD/PATH?a=A&B=b" );
  ASSERT_TRUE(URL.IsValid());

  ASSERT_EQ("https", URL.m_Scheme);     // notice it's now lowercase
  ASSERT_EQ("ESPN.com", URL.m_Host);    // case unchanged
  ASSERT_EQ("BOLD/PATH", URL.m_Path);
  ASSERT_EQ("a=A&B=b", URL.m_Query);
}

TEST_F(UrlTest, ipv6) {

  clParseURL URL = clParseURL::ParseURL( "https://[fe80::9a01:a7ff:feb1:7dc9]:80/corporateshark/LUrlParser" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("[fe80::9a01:a7ff:feb1:7dc9]", URL.m_Host);
}

TEST_F(UrlTest, ipv4) {

  clParseURL URL = clParseURL::ParseURL( "https://10.0.3.243/corporateshark/LUrlParser" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("10.0.3.243", URL.m_Host);
}

TEST_F(UrlTest, parens) {

  clParseURL URL = clParseURL::ParseURL( "https://en.wikipedia.org/wiki/Joe_Malone_(ice_hockey)" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("wiki/Joe_Malone_(ice_hockey)", URL.m_Path);
}

TEST_F(UrlTest, trailingdot) {

  clParseURL URL = clParseURL::ParseURL( "http://foo.com/blah_blah." );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("blah_blah.", URL.m_Path);

  URL = clParseURL::ParseURL( "http://foo.com/blah_blah/." );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("blah_blah/.", URL.m_Path);
}

TEST_F(UrlTest, specialchars) {

  clParseURL URL = clParseURL::ParseURL( "https://duckduckgo.com/?q=mark+twain&atb=v23_c&ia=web" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("q=mark+twain&atb=v23_c&ia=web", URL.m_Query);
}

TEST_F(UrlTest, escapechars) {

  clParseURL URL = clParseURL::ParseURL( "https://duckduckgo.com/?q=mark%20twain" );
  ASSERT_TRUE(URL.IsValid());
  ASSERT_EQ("q=mark%20twain", URL.m_Query);
}

/* // these currently still return valid

TEST_F(UrlTest, controlchars) {

  clParseURL URL;
  URL = clParseURL::ParseURL( "https://en.wikipedia.org/bell\007/" );
  ASSERT_FALSE(URL.IsValid());

  URL = clParseURL::ParseURL( "https://en.wikipedia.org/line\njere/" );
  ASSERT_FALSE(URL.IsValid());
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int status= RUN_ALL_TESTS();
  return status;
}
