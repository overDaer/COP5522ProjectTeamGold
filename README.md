# COP5522 Class Project

This is the COP5522 class project repository.

## Documentation

Access the video going over the project here: https://youtu.be/iUrCV7SN1nw

The `docs` folder contains the following documents:

- Project proposal.

All documents are created using LaTeX then typset to PDF. Details are in the `README` contained in the `docs` folder.

## Code Structure

The serial and pThread variants of the program are located in the `serial` and `pthreads` folders respectively.

## Running the code

### Visual Studio Code (Windows)

- Install the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

- Install the MinGW-w64 compiler as explained in this [blog post](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

- Open the folder in VS Code containing the variant you want to run. For example, to run the serial variant, open the `serial` folder is VS Code.

- Click **Run** -> **Start Debugging** or **Run** -> **Start Run without Debugging**.

### CLion (Windows)

The instructions below assume you have properly configured CLion to use the WSL2 toolchain.

- Open the folder in CLion containing the variant you want to run. For example, to run the serial variant, open the `serial` folder is VS Code.

- Click **Build** -> **Rebuild Project**.

- Click `Shift + F10` to run the program or `Shift + F9` to debug the program.
