
#include "Layer_CommandStorage.h"

//	Qt
#include <QtGui/QAction>

CommandStorage* CommandStorage::instance() {
	if (st_ == 0)
		st_ = new CommandStorage();

	return st_;
}

void CommandStorage::registerCommand_S(const StaticCmd& cmd) {
	StaticCommandID id = cmd.id;

	if (Scmd_.contains(id))
		delete Scmd_[id];
	
	QString keya = QString(); /* not Shortcut */
	if (!cmd.shortcut.isEmpty()) {
		keya = QString(" ") + cmd.shortcut.toString(QKeySequence::NativeText);
	}
	QAction* action = new QAction(cmd.icon, cmd.name + keya, 0);
	action->setShortcut(cmd.shortcut);
	action->setData(id);
	action->setIcon(cmd.icon);
	QObject::connect(action, SIGNAL(triggered()), cmd.reciever, qPrintable(cmd.slot));
	Scmd_[id] = action;
}


void CommandStorage::registerCommand_D(const DinamicCmd& cmd) {
	DynamicCommandID id = cmd.id;

	if (Dcmd_.contains(id))
		delete Dcmd_[id];
	
	QString keya = QString(); /* not Shortcut */
	if (!cmd.shortcut.isEmpty()) {
		keya = QString(" ") + cmd.shortcut.toString(QKeySequence::NativeText);
	}
	QAction* action = new QAction(cmd.icon, cmd.name + keya, 0);
	action->setShortcut(cmd.shortcut);
	action->setData(id);
	if (cmd.checkaBle_)  {
		action->setCheckable ( true );
	}
	action->setEnabled ( cmd.enables );
	action->setIcon(cmd.icon);
	QObject::connect(action, SIGNAL(triggered()), cmd.reciever, qPrintable(cmd.slot));
	Dcmd_[id] = action;
}

QAction* CommandStorage::actS(StaticCommandID id) {
	return Scmd_[id];
}


QAction* CommandStorage::actD(DynamicCommandID id) {
	return Dcmd_[id];
}

CommandStorage* CommandStorage::st_ = 0;







