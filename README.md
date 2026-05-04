# 🏦 Project 3 — Bank Client Management System

> A complete console-based banking system built in C++ — managing real client data through structured programming, file persistence, and clean Divide & Conquer design.

---

## 🚀 Project Overview

This project simulates a real-world **Bank Client Management System**.

Imagine a bank operator sitting at a terminal:

- They need to register a new client with full account details
- They need to look up a client instantly by account number
- They need to update information or remove a client permanently
- All data must survive between sessions — saved to a file, reloaded on startup

This project makes all of that happen.

We are not building a UI.

We are building the **engine** behind the banking operation.

---

## ⚙️ Core Functionalities

The system supports the following operations:

| Operation | Description |
|---|---|
| 📋 **Show All Clients** | Display all registered clients in a formatted table |
| ➕ **Add New Client** | Register one or more new clients with full validation |
| 🗑️ **Delete Client** | Remove a client permanently by account number |
| ✏️ **Update Client Info** | Modify an existing client's details |
| 🔍 **Find Client** | Search and display a specific client by account number |
| 🚪 **Exit** | Close the system cleanly |

---

## 🏗️ Architecture Design

The project follows a clean **Divide & Conquer** structure.

Each responsibility is isolated into a dedicated function:

```
main()
 └── ShowMainMenu()
      ├── ShowAllClientsScreen()       → LoadClientsDataFromFile() → PrintClientRecord()
      ├── ShowAddNewClientsScreen()    → ReadNewClient() → AddClientToFile()
      ├── ShowDeleteClientScreen()     → FindClient() → MarkForDelete() → SaveToFile()
      ├── ShowUpdateClientScreen()     → FindClient() → ChangeClientRecord() → SaveToFile()
      └── ShowFindClientScreen()       → FindClientByAccountNumber() → PrintClientCard()
```

No function does more than one job.

No logic is repeated.

Every operation is composable and reusable.

---

## 💾 Data Persistence Strategy

Client data is stored in a plain text file using a custom separator format:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

**On every startup** → data is read from file and loaded into a `vector<sClient>`

**After every operation** → the vector is written back to the file

This creates a lightweight but reliable persistence layer — no database required.

### File ↔ Memory Cycle:

```
File (Clients.txt)
     ↓  LoadClientsDataFromFile()
vector<sClient>  ←→  All operations happen here
     ↓  SaveClientsDataToFile()
File (Clients.txt)  ← Updated automatically
```

---

## 🧱 Data Structure

```cpp
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool   MarkForDelete;   // soft-delete flag
};
```

Delete operations use a **soft-delete flag** (`MarkForDelete = true`) before the file is rewritten — a real-world pattern used in production systems.

---

## 🎯 What This Project Teaches

- Real-world system design from scratch
- File I/O in C++ (`fstream`, `ios::in`, `ios::out`, `ios::app`)
- Data serialization and deserialization (string ↔ struct)
- Vector-based in-memory data management
- Soft-delete pattern for safe data removal
- Enum-driven menu navigation
- Clean code through single-responsibility functions
- Input validation and duplicate prevention
- Formatted console output using `iomanip`

More importantly:

It shows how to take a real-world scenario and translate it into a structured, maintainable C++ program.

---

## 🛠️ Tech Stack

| | |
|---|---|
| **Language** | C++ |
| **IDE** | Visual Studio |
| **Type** | Console Application |
| **Paradigm** | Structured Programming — Divide & Conquer |
| **Storage** | Text File (File I/O) |
| **STL Used** | `vector`, `string`, `fstream`, `iomanip` |

---

## 📦 Project Versions

This project is the base of a growing banking system that evolves across multiple extensions.

Each version lives in its **own dedicated repository** with its own full README.

| Version | Repo | Key Additions |
|---|---|---|
| **Bank 1** *(you are here)* | ← this repo | CRUD operations, file persistence, clean architecture |
| **Bank 1 — 1st Extension** | *(separate repo)* | Deposit, Withdraw, Total balance view |
| **Bank 1 — 2nd Extension** | *(separate repo)* | Role-based user permissions, login, input validation |

> Each extension builds directly on top of the previous version — same system, growing responsibilities.

---

## 🏁 Milestone

This project marks a key stage in the roadmap:

- ✅ First real-world banking system built in C++
- ✅ Part of **Course 7 — Algorithms & Problem Solving – Level 3**
- ✅ Applies 50 problems worth of problem-solving experience into a single coherent system

الحمد لله الذي هدانا لهذا وما كنا لنهتدي لولا أن هدانا الله.

---

## 🙏 Gratitude

Thank you to:

- **Programming Advices Platform**
- **Dr. Mohammed Abu-Hadhoud**

**[ https://programmingadvices.com ]**

Not just an instructor — a guide who understands the right time to teach each concept.

Because the real difference between a strong developer and a weak one is:

- Proper progression
- Correct structure
- The right concept at the right time

And that is exactly what this roadmap delivers.

---

## 🔥 Final Thought

This is not just a banking system.

It is proof that structured thinking, clean functions, and disciplined design can turn a set of requirements into a working, maintainable application.

And we are only getting started.
