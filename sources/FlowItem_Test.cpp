#include "FlowItem_Test.hpp"

#include "FlowItemConnection.hpp"

const QString itemTitle("DUMP");

FlowItem_Test::FlowItem_Test(BasicLogger *logger) : FlowItem_User(itemTitle, logger, LayoutOwnershipMode::make_link) {
  AddInputPort();
}

FlowItem_Test::~FlowItem_Test() {}

bool FlowItem_Test::DropEventHandler() {
  p_logger->Log(QString("'%1-DROP' was called").arg(itemTitle));
  return true;
}

bool FlowItem_Test::ExecuteEventHandler() {
  p_logger->Log(QString("'%1-EXECUTE' was called").arg(itemTitle));

  if (!inputPorts[0]->connections.size() || !inputPorts[0]->connections[0]->p_portA) {
    p_logger->Error("Flow item is not connected!");
    return false;
  }

  if (!inputPorts[0]->GetLayout()) {
    p_logger->Error("Can't access read layout data.");
    return false;
  }

  Layout *p_layout = p_resultLayout;

  p_logger->Log(QString("\nDumping information for file '%1'...").arg(QString::fromStdWString(p_layout->fileName)));
  p_logger->Log(QString("\tInput file has %1 libraries").arg(p_layout->libraries.size()));

  
  for (size_t i = 0; i < p_layout->libraries.size(); ++i) {
    p_logger->Log(QString("\t  - Library [%1] has name '%2' and contains %3 elements:").arg(i).arg(QString::fromStdString(p_layout->libraries[i]->name)).arg(p_layout->libraries[i]->elements.size()));
    for (size_t j = 0; j < p_layout->libraries[i]->elements.size(); ++j)
      p_logger->Log(QString("\t    * %1 (contains %2 geometries)").arg(QString::fromStdString(p_layout->libraries[i]->elements[j]->name)).arg(p_layout->libraries[i]->elements[j]->geometries.size()));
    p_logger->Log(QString("\t  - Library [%1] also contains %2 layers (in order of appearance):").arg(i).arg(p_layout->libraries[i]->layers.size()));
    for (size_t j = 0; j < p_layout->libraries[i]->layers.size(); ++j)
      if(p_layout->libraries[i]->layers[j].name.empty())
        p_logger->Log(QString("\t    * %1").arg(p_layout->libraries[i]->layers[j].layer));
      else
        p_logger->Log(QString("\t    * %1 [%2]").arg(p_layout->libraries[i]->layers[j].layer).arg(p_layout->libraries[i]->layers[j].name.c_str()));
  }
  p_logger->Log(QString("Dumping information for file '%1' is done.\n").arg(QString::fromStdWString(p_layout->fileName)));

  return false;
}

bool FlowItem_Test::OpenResultsEventHandler() {
  p_logger->Log(QString("'%1-OPENRESULTS' was called").arg(itemTitle));
  return true;
}

bool FlowItem_Test::ResetEventHandler() {
  p_logger->Log(QString("'%1-RESET' was called").arg(itemTitle));
  return true;
}

bool FlowItem_Test::ShowPropertesEventHandler() {
  p_logger->Log(QString("'%1-PROPERTIES' was called").arg(itemTitle));
  return true;
}

QString FlowItem_Test::GetInfoString() {
  return QString("%1 module info string").arg(itemTitle);
}

// Exported functions

__declspec(dllexport) FlowItemType GetType() {
  return FlowItemType::userdefined;
}

__declspec(dllexport) QString GetInfo() {
  return QString("This library contains an example of FlowItem DLL usage.");
}

__declspec(dllexport) QString GetCaption() {
  return itemTitle;
}

__declspec(dllexport) QString GetAuthor() {
  return QString("Dmitry A. Bulakh, DICD, NRU MIET");
}

__declspec(dllexport) FlowItem *GetItem(BasicLogger *logger) {
  return new FlowItem_Test(logger);
}

__declspec(dllexport) void FreeItem(FlowItem **item) {
  if (!item)
    return;
  if (!*item)
    return;
  delete *item;
  *item = nullptr;
}
