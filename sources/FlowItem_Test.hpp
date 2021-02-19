#pragma once

#include <FlowItem_User.hpp>

class FlowItem_Test : public FlowItem_User {
public:
  FlowItem_Test(BasicLogger *logger);
  virtual ~FlowItem_Test();
public:
  bool DropEventHandler() override final;
  bool ExecuteEventHandler() override final;
  bool OpenResultsEventHandler() override final;
  bool ResetEventHandler() override final;
  bool ShowPropertesEventHandler() override final;
  QString GetInfoString() override final;
};

__declspec(dllexport) FlowItemType  GetType();
__declspec(dllexport) QString       GetInfo();
__declspec(dllexport) QString       GetCaption();
__declspec(dllexport) QString       GetAuthor();
__declspec(dllexport) FlowItem *    GetItem(BasicLogger *logger);
__declspec(dllexport) void          FreeItem(FlowItem **item);

