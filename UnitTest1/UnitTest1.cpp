#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.3/lab10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestSearchFriend) {
            const string testFilename = "t.txt";
            ofstream testFile(testFilename);
            testFile << "John Doe,123-456-7890,1 1 2000\n";
            testFile.close();

            stringstream capturedOutput;
            streambuf* originalCoutBuffer = cout.rdbuf();
            cout.rdbuf(capturedOutput.rdbuf());

            SearchFriend(testFilename, "John");
            cout.rdbuf(originalCoutBuffer);

            string expectedOutput = "Full Name: John Doe, Phone: 123-456-7890, Birthday: 1 1 2000\n";
            Assert::IsTrue(capturedOutput.str().find(expectedOutput) != string::npos, L"Expected information not found for 'John'");

            remove(testFilename.c_str());
        }

        TEST_METHOD(TestValidateDate) {
            Assert::IsTrue(ValidateDate(1, 1, 2000));
            Assert::IsFalse(ValidateDate(0, 1, 2000));
        }
	};
}
