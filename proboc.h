#ifndef _PROBOC_MAIN_H_
#define _PROBOC_MAIN_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

class IMemberDescriptor {
public:
  virtual std::string StructMember() = 0;
  virtual std::string ForwardDeclarations() = 0;
  virtual std::string FunctionDefinitions() = 0;
/*  virtual std::string
  IntegrationTestSetValue(const std::string &msg_inst_name) = 0;
  virtual std::string
  IntegrationTestVerify(const std::string &msg_inst_name) = 0;*/
  virtual std::string UnitTest() = 0;
  virtual void SetMessageName(const std::string &message_name) = 0;
  virtual std::string GetIdentifier() = 0;
};

class Int32Member : public IMemberDescriptor {
public:
  Int32Member(const std::string &message_name, long long index,
              const std::string &identifier);
  std::string StructMember() override;
  std::string ForwardDeclarations() override;
  std::string FunctionDefinitions() override;
  std::string IntegrationTestSetValue(const std::string &msg_inst_name);
  std::string IntegrationTestVerify(const std::string &msg_inst_name);
  std::string UnitTest();
  void SetMessageName(const std::string &message_name);
  std::string GetIdentifier() { return identifier; }
private:
  long long index;
  std::string identifier, message_name;
};

class Int16Member : public IMemberDescriptor {
public:
  Int16Member(const std::string &message_name, long long index,
              const std::string &identifier);
  std::string StructMember() override;
  std::string ForwardDeclarations() override;
  std::string FunctionDefinitions() override;
  std::string IntegrationTestSetValue(const std::string &msg_inst_name);
  std::string IntegrationTestVerify(const std::string &msg_inst_name);
  std::string UnitTest(); 
  void SetMessageName(const std::string &message_name);
  std::string GetIdentifier() { return identifier; }

private:
  long long index;
  std::string identifier, message_name;
};

class Int8Member : public IMemberDescriptor {
public:
  Int8Member(const std::string &message_name, long long index,
             const std::string &identifier);
  std::string StructMember() override;
  std::string ForwardDeclarations() override;
  std::string FunctionDefinitions() override;
  std::string IntegrationTestSetValue(const std::string &msg_inst_name);
  std::string IntegrationTestVerify(const std::string &msg_inst_name);
  std::string UnitTest();
  void SetMessageName(const std::string &message_name);
  std::string GetIdentifier() { return identifier; }

private:
  long long index;
  std::string identifier, message_name;
};

class StringMember : public IMemberDescriptor {
public:
  StringMember(const std::string &message_name, long long index,
               const std::string &identifier, size_t size);
  std::string StructMember() override;
  std::string ForwardDeclarations() override;
  std::string FunctionDefinitions() override;
  std::string IntegrationTestSetValue(const std::string &msg_inst_name);
  std::string IntegrationTestVerify(const std::string &msg_inst_name);
  std::string UnitTest();
  void SetMessageName(const std::string &message_name);
  std::string GetIdentifier() { return identifier; }

private:
  long long index;
  std::string identifier, message_name;
  size_t size;
};

struct MessageDescriptor {
  std::map<long long, std::unique_ptr<IMemberDescriptor> > members;

  std::string RenderHeader();
  std::string RenderCppFile();
  std::string RenderTestFile();

  std::string identifier;
  bool processed = false;
};

extern std::vector<MessageDescriptor> probo_messages;

#endif /* _PROBOC_MAIN_H_ */
