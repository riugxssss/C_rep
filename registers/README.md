🧪 Register Simulation in C
This project simulates three hardware-style registers (8-bit, 16-bit, and 32-bit) using C structs, bitfields, and unions. It is designed for low-level systems or embedded programmers who want to model register-level behavior in software. TESTED ON LINUX SISTEM

📦 Features
✅ Support for 8-bit, 16-bit, and 32-bit registers.
✅ Bitfield access for individual flags and fields.
✅ Raw access to the entire register using a unified modify field.
✅ Compile-time endianness detection for correct bitfield layout.
✅ Optional runtime endianness check.
✅ Basic bit manipulation utilities (set, clear, toggle).
✅ Modular design via registers_utils.h.

🧱 Registers Overview
Each register (al, ax, eax) is implemented with a union:

Direct access via modifyal, modifyax, modifyeax.

Field-level access via bitaccess8, bitaccess16, bitaccess32.

Registers instance;
instance.al.bitaccess8.enable = 1;        // Set 'enable' bit in 8-bit register
instance.ax.modifyax = 0xFFFF;            // Write raw 16-bit value
instance.eax.bitaccess32.status = 0x80;   // Set status field in 32-bit register
📂 File Structure

Edit
.
├── main.c                # Main simulation logic
├── registers_utils.h     # Bit manipulation and print functions
⚙️ Bit Manipulation Utilities
Implemented functions (in registers_utils.h):


void set_bit(uint8_t* reg, uint8_t bit);
void clear_bit(uint8_t* reg, uint8_t bit);
void toggle_bit(uint8_t* reg, uint8_t bit);
void print_registers(uint32_t reg, int size_in_bits);
These utilities allow safe and readable operations on individual bits.

🧪 Example Output
Edit
START
COMPILE-TIME: Little-endian system
RUNTIME: Little-endian system
[8-BIT]   00000111
[16-BIT]  0000000000001100
[32-BIT]  00000000100000000000000000000001
END
🧠 Notes
Bitfield layout depends on compiler behavior. Use with care if targeting real hardware.

Endianness handling ensures the struct behaves consistently across platforms.

Can be extended to simulate more registers or features like read-only bits, volatile behavior, etc.

📌 Requirements
A C compiler (e.g., gcc, clang)

Works on Windows, Linux, or macOS

🏁 Compile & Run
bash
Copy
Edit
gcc -o register_sim main.c
./register_sim

📜 License
This project is open-source and can be used freely for learning or development purposes.

