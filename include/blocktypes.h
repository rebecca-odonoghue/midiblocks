#ifndef BLOCKTYPES
#define BLOCKTYPES

#include <QList>
#include <QString>

// Enum describing the types of processing block
typedef enum {PITCH_SHIFT,
              ARPEGGIATOR,
              MONOPHONIC,
              CHORDIFY,
              GATE} BlockType;

// Enum describing the different patterns that can be applied to an
// Arpeggiator block
typedef enum {ASCENDING,
              DESCENDING,
              PING_PONG,
              RANDOM} ArpeggiatorPattern;

// Enum describing the different modes that can be applied to a Gate block
typedef enum {QUEUE,
              FIRST_HOLD,
              LAST_HOLD} GateMode;

// Descriptions of ArpeggiatorPatterns to be displayed in GUI
static const QStringList patternNames = {"Ascending Scale",
                                         "Descending Scale",
                                         "Ping-pong",
                                         "Random"};

// Descriptions of GateModes to be displyed in GUI
static const QStringList modeNames = {"Queue",
                                      "First Hold",
                                      "Last Hold"};

#endif // BLOCKTYPES

