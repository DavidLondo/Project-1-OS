typedef enum {
    ADD,
    INC,
    SUB,
    NOP
} InstructionType;

typedef struct {
    InstructionType type;
    int operand1;
    int operand2;
    int result;
} Instruction;
