/*
 * MCP2515.h
 *
 * Created: 02.10.2017 18:47:15
 *  Author: hermansu
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_


#define RESET_INSTRUCTION       0xC0// Instruction for immediate reset
#define READ_INSTRUCTION        0x03// Read register
#define WRITE_INSTRUCTION       0x02// Write register
#define READRX_INSTRUCTION      0x90// 10010mn0 - m,n is address of the RX buffer
#define LOADTX_INSTRUCTION      0x40// 01000abc - a,b,c is address of the TX buffer
#define RTS_INSTRUCTION         0x80// 10000abc - a,b,c is address of the TX buffer
#define READSTAT_INSTRUCTION    0xA0// Read device status instructio
#define RXSTAT_INSTRUCTION      0xB0// Read receive buffer status instruction
#define BITMODIFY_INSTRUCTION   0x05// For specific bit modifications

// Flags in the result of READ STATE instruction
// (Can be used as bit masks for each flag)
#define STATE_RX0_FULL          (0x01 << 0)// 00000001
#define STATE_RX1_FULL          (0x01 << 1)// 00000010
#define STATE_TX0_TXREQ         (0x01 << 2)// 00000100
#define STATE_TX0_EMPTY         (0x01 << 3)// 00001000
#define STATE_TX1_TXREQ         (0x01 << 4)// 00010000
#define STATE_TX1_EMPTY         (0x01 << 5)// 00100000
#define STATE_TX2_TXREQ         (0x01 << 6)// 01000000
#define STATE_TX2_EMPTY         (0x01 << 7)// 1


//RX status instruction - mask bits in result state
#define RM_POS                  (0x03 << 6)// Received message position
#define EXT_MSG                 (0x01 << 4)// Is message extended?
#define REMOTE_MSG              (0x01 << 3)// Is message remote?
#define AFM                     (0x07 << 0)// Acceptance filter match

// Masks for informations contained in the result of RX state instruction
#define RXSTATE_MSG_POSITION    0xC0// xx000000
#define RXSTATE_MSG_TYPE        0x18// 000xx000
#define RXSTATE_ACCEPT_FILTER   0x07// 00000xx

// Indexes of RX and TX buffers
#define NO_FILTERS              6
#define NO_MASKS                2
#define NO_TX_BUFFERS           3
#define NO_RX_BUFFERS           2
#define TXB0                    0// Transmit buffer 0
#define TXB1                    1// Transmit buffer 1
#define TXB2                    2// Transmit buffer 2
#define RXB0                    0// Receive buffer 0
#define RXB1                    1// Receive buffer 1

//    MCP2515 buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define RXF0                   0// RXB0 filter 0 (or RXB1 filter 0, when rollover is active)
#define RXF1                   1// RXB0 filter 1 (or RXB1 filter 1, when rollover is active)
#define RXF2                   2// RXB1 filter 2
#define RXF3                   3// RXB1 filter 3
#define RXF4                   4// RXB1 filter 4
#define RXF5                   5// RXB1 filter 5

// Transmit & receive error counters
#define TEC                     0x1C// Transmit error counter
#define REC                     0x1D// Receive error counter

// Bit definitions for register BFPCTRL
// (RXn buffer pin control and status)
#define BFPCTRL                 0x0C
#define B1BFS                   5// RW-0, RX1BF pin state bit
#define B0BFS                   4// RW-0, RX0BF pin state bit
#define B1BFE                   3// RW-0, RX1BF pin function enable bit
#define B0BFE                   2// RW-0, RX0BF pin function enable bit
#define B1BFM                   1// RW-0, RX1BF pin operation mode bit
#define B0BFM                   0// RW-0, RX0BF pin operation mode bit

// Bit definitions for register CANCTRL
// (CAN control register)
#define CANCTRL                 0x0F
#define REQOP2                  7// RW-1, Request operation mode bit 2
#define REQOP1                  6// RW-0, Request operation mode bit 1
#define REQOP0                  5// RW-0, Request operation mode bit 0
#define ABAT                    4// RW-0, Abort all pending transmissions bit
#define OSM                     3// RW-0, One shot mode
#define CLKEN                   2// RW-1, CLKOUT pin enable
#define CLKPRE1                 1// RW-1, CLKOUT pin prescaler 1
#define CLKPRE0                 0// RW-1, CLKOUT pin prescaler 0

// Bit definitions for register CANSTAT
// (CAN status register)
#define CANSTAT                 0x0E
#define OPMOD2                  7// R-1, Operation mode bit 2
#define OPMOD1                  6// R-0, Operation mode bit 1
#define OPMOD0                  5// R-0, Operation mode bit 0
#define ICOD2                   3// R-0, Interrupt flag code bit 2
#define ICOD1                   2// R-0, Interrupt flag code bit 1
#define ICOD0                   1// R-0, Interrupt flag code bit 0

// Bit definitions for register CNF3
// (Configuration 3 register)
#define CNF3                    0x28
#define SOF                     7// RW-0, Start of frame signal bit
#define WAKFIL                  6// RW-0, Wake-up filter bit
#define PHSEG22                 2// RW-0, PS2 bit 2
#define PHSEG21                 1// RW-0, PS2 bit 1

#define PHSEG20                 0// RW-0, PS2 bit

// Bit definitions for register CNF2
// (Configuration 2 register)
#define CNF2                    0x29
#define BTLMODE                 7// RW-0, PS bit time length bit
#define SAM                     6// RW-0, Sample point configuration bit
#define PHSEG12                 5// RW-0, PS1 length bit 2
#define PHSEG11                 4// RW-0, PS1 length bit 1
#define PHSEG10                 3// RW-0, PS1 length bit 0
#define PRSEG2                  2// RW-0, Propagation segment length bit 2
#define PRSEG1                  1// RW-0, Propagation segment length bit 1
#define PRSEG0                  0// RW-0, Propagation segment length bit 0

/ Bit definitions for register CNF1
// (Configuration 1 register)
#define CNF1                    0x2A
#define SJW1                    7// RW-0, Synchronization jump width length bit 1
#define SJW0                    6// RW-0, Synchronization jump width length bit 0
#define BRP5                    5// RW-0, Baud rate prescaler bit 5
#define BRP4                    4// RW-0, Baud rate prescaler bit 4
#define BRP3                    3// RW-0, Baud rate prescaler bit 3
#define BRP2                    2// RW-0, Baud rate prescaler bit 2
#define BRP1                    1// RW-0, Baud rate prescaler bit 1
#define BRP0                    0// RW-0, Baud rate prescaler bit 0

// Bit definitions for register CANINTE
// (Interrupt enable register)
#define CANINTE                 0x2B
#define MERRE                   7// RW-0, Message error interrupt enable bit
#define WAKIE                   6// RW-0, Wakeup interrupt enable bit
#define ERRIE                   5// RW-0, Error interrupt enable bit
#define TX2IE                   4// RW-0, Transmit buffer 2 empty interrupt enable b
it
#define TX1IE                   3// RW-0, Transmit buffer 1 empty interrupt enable b
it
#define TX0IE                   2// RW-0, Transmit buffer 0 empty interrupt enable b
it
#define RX1IE                   1// RW-0, Receive buffer 1 full interrupt enable bit
#define RX0IE                   0// RW-0, Receive buffer 0 full interrupt enable bit

// (Interrupt flag register)
#define CANINTF                 0x2C
#define MERRF                   7// RW-0, Message error interrupt flag bit
#define WAKIF                   6// RW-0, Wakeup interrupt flag bit
#define ERRIF                   5// RW-0, Error interrupt flag bit
#define TX2IF                   4// RW-0, Transmit buffer 2 empty interrupt flag bit
#define TX1IF                   3// RW-0, Transmit buffer 1 empty interrupt flag bit
#define TX0IF                   2// RW-0, Transmit buffer 0 empty interrupt flag bit
#define RX1IF                   1// RW-0, Receive buffer 1 full interrupt flag bit
#define RX0IF                   0// RW-0, Receive buffer 0 full interrupt flag bit

// Bit definitions for register EFLG
// (Error flag register)
#define EFLG                    0x2D
#define RX1OVR                  7// RW-0, Receive buffer 1 overflow flag bit
#define RX0OVR                  6// RW-0, Receive buffer 0 overflow flag bit
#define TXBO                    5// R-0, Bus-off error flag bit
#define TXEP                    4// R-0, Transmit error - passive flag bit
#define RXEP                    3// R-0, Receive error - passive flag bit
#define TXWAR                   2// R-0, Transmit error warning flag bit
#define RXWAR                   1// R-0, Receive error warning flag bit
#define EWARN                   0// R-0, Error warning flag bit

// Bit definitions for registers TXBnCTRL
// (Transmit buffer n control register)
#define TXBnCTRL(n)             0x30+(n*0x10)
#define TXB0CTRL                TXBnCTRL(0)
#define TXB1CTRL                TXBnCTRL(1)
#define TXB2CTRL                TXBnCTRL(2)
#define ABTF                    6// R-0, Message aborted flag bit
#define MLOA                    5// R-0, Message lost arbitration bit
#define TXERR                   4// R-0, Transmit error detected bit
#define TXREQ                   3// RW-0, Message transmit request bit
#define TXP1                    1// RW-0, Transmit buffer priority bit 1
#define TXP0                    0// RW-0, Transmit buffer priority bit 0

// Bit definitions for registers TXBnDLC
// (Transmit buffer data length control)
#define TXBnDLC(n)              0x35+(n*0x10)
#define TXB0DLC                 TXBnDLC(0)
#define TXB1DLC                 TXBnDLC(1)
#define TXB2DLC                 TXBnDLC(2)
#define RTR                     6// RW-x, Remote transfer request
#define DLC3                    3// RW-x, Data length code bit 3
#define DLC2                    2// RW-x, Data length code bit 2
#define DLC1                    1// RW-x, Data length code bit 1
#define DLC0                    0// RW-x, Data length code bit

// Bit definitions for register TXBnSIDH
// (Transmit buffer n - standard identifier high)
#define TXBnSIDH(n)             0x31+(n*0x10)
#define TXB0SIDH                TXBnSIDH(0)
#define TXB1SIDH                TXBnSIDH(1)
#define TXB2SIDH                TXBnSIDH(2)
#define SID10                   7// RW-x, Standard identifier, bit 10
#define SID9                    6// RW-x, Standard identifier, bit 9
#define SID8                    5// RW-x, Standard identifier, bit 8
#define SID7                    4// RW-x, Standard identifier, bit 7
#define SID6                    3// RW-x, Standard identifier, bit 6
#define SID5                    2// RW-x, Standard identifier, bit 5
#define SID4                    1// RW-x, Standard identifier, bit 4
#define SID3                    0// RW-x, Standard identifier, bit 3

// Bit definitions for register TXBnSIDL
// (Transmit buffer n - standard identifier low)
#define TXBnSIDL(n)             0x32+(n*0x10)
#define TXB0SIDL                TXBnSIDL(0)
#define TXB1SIDL                TXBnSIDL(1)
#define TXB2SIDL                TXBnSIDL(2)
#define SID2                    7// RW-x, Standard identifier, bit 2
#define SID1                    6// RW-x, Standard identifier, bit 1
#define SID0                    5// RW-x, Standard identifier, bit 0
#define EXIDE                   3// RW-x, Extended identifier enable bit
#define EID17                   1// RW-x, Extended identifier, bit 17
#define EID16                   0// RW-x, Extended identifier, bit 16


#endif /* MCP2515_H_ */