# FixItNow -- Appliance Repair Simulator

Hello! I built FixItNow to simulate how a repair shop handles appliance repairs. The program loads the staff roster, appliance catalog, and incoming requests. It assigns work to technicians, tracks repairs through completion, and exports CSV reports. The project also serves as a reference for current and future students learning object-oriented programming in C++.

## Demo

Run the included demo from the repository root on Linux or WSL with `g++` and `make` installed.

```bash
make demo
```

This builds the program, creates the `Rapoarte/` output folder, and runs the sample inputs through the Romanian console menus. The demo completes four repairs, rejects one request for an unsupported appliance, and writes six CSV reports.

Technician 2 receives request 504. When that request arrives, the three technicians already have 4, 2, and 3 estimated repair hours assigned, respectively. You can see the result in `Rapoarte/Raport_Cereri_Complet.csv`.

```text
Tehnician 2 primeste cererea 504
Tehnician 2 finalizeaza cererea 504
```

## Compilation

Use `make` to build, `make run` to open the interactive menus, or `make clean` to remove the executable. To build and run manually, use the following commands from the project folder.

```bash
g++ *.cpp -o a.out
mkdir -p Rapoarte
./a.out
```

To run the sample manually, enter each menu number separately.

1. Enter **1 -> 4 -> 0** to load the staff roster.
2. Enter **2 -> 1 -> 0** to load the appliance catalog.
3. Enter **3 -> 1 -> 3** to load requests and start the simulation.
4. When the simulation finishes, enter **4** to export the reports and **0 -> 0** to exit.

## Classes Used

`Cerere` tracks a repair and its status. `Tehnician` stores a technician's skills and assigned workload. `ServiceManager` loads the input files, coordinates the simulation, and writes the reports.

## Step 1 -- Load and validate requests

The three files in `tests/` contain comma-separated sample data. The simulator checks incoming requests against the appliance catalog and records rejected requests separately. The demo staff records use fictional names and identifiers.

## Step 2 -- Assign technicians

A technician must match the appliance brand or type and have fewer than three active requests. If several technicians qualify, the simulator picks the one with the lowest total estimated repair time already assigned.

## Step 3 -- Simulate repairs and export reports

The simulation advances in time steps and moves repairs from waiting to in progress and then to completed. CSV reports include request status, technician assignments, rejected appliances, and payroll.

## Project Background

The original assignment and my implementation are shared as reference material for current and future students. Students work on a similar assignment and write their own solutions. FixItNow gives them an example of how to structure and implement a C++ application.

## Demo Output

```text
Gestiune Cereri
Press 1 Incarca Cererile
Press 2 Afiseaza Lista Cereri
Press 3 Porneste Simularea In Timp Real
Press 4 Generare Rapoarte CSV
Press 0 Inapoi
Optiunea aleasa:
[Timp 1]
   Receptioner Demo a inregistrat cererea 501
   Receptioner Demo a inregistrat cererea 502
   Receptioner Demo a inregistrat cererea 503
   Tehnician 1 primeste cererea 501
   Tehnician 2 primeste cererea 502
   Tehnician 3 primeste cererea 503
   Tehnician 1 proceseaza cererea 501 (raman 4 ore)
   Tehnician 2 proceseaza cererea 502 (raman 2 ore)
   Tehnician 3 proceseaza cererea 503 (raman 3 ore)
   Cereri in asteptare: -

[Timp 2]
   Receptioner Demo a inregistrat cererea 504
   Tehnician 2 primeste cererea 504
   Tehnician 1 proceseaza cererea 501 (raman 3 ore)
   Tehnician 2 proceseaza cererea 502 (raman 1 ore)
   Tehnician 2 finalizeaza cererea 502
   Tehnician 3 proceseaza cererea 503 (raman 2 ore)
   Tehnician 2 proceseaza cererea 504 (raman 1 ore)
   Tehnician 2 finalizeaza cererea 504
   Cereri in asteptare: -

[Timp 3]
   Tehnician 1 proceseaza cererea 501 (raman 2 ore)
   Tehnician 3 proceseaza cererea 503 (raman 1 ore)
   Tehnician 3 finalizeaza cererea 503
   Cereri in asteptare: -
```
