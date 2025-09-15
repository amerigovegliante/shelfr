#include "../../headers/gui/defaultview.h"
#include <QLabel>
#include <QVBoxLayout>

DefaultView::DefaultView(QWidget *parent) : BaseView(parent)
{
    setupUI();
}

void DefaultView::setupUI()
{
    layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(50, 50, 50, 50);

    // Title
    title = new QLabel("Welcome to Shelfr", this);
    title->setObjectName("welcome-title");
    title->setAlignment(Qt::AlignCenter);

    // Subtitle
    subtitle = new QLabel("Your personal media library manager", this);
    subtitle->setObjectName("welcome-subtitle");
    subtitle->setAlignment(Qt::AlignCenter);

    // Features list
    features = new QLabel(
        "• Manage Books, Films, Music, and Video Games\n"
        "• Create custom collections\n"
        "• Search and organize your media\n"
        "• Beautiful dark/light theme support", this);
    features->setObjectName("welcome-features");
    features->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addWidget(features);
    layout->addStretch();
}