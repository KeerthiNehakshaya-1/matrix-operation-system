const operation = document.getElementById("operation");

const rowsA = document.getElementById("rowsA");
const colsA = document.getElementById("colsA");

const rowsB = document.getElementById("rowsB");
const colsB = document.getElementById("colsB");

const matrixAGrid = document.getElementById("matrixAGrid");
const matrixBGrid = document.getElementById("matrixBGrid");

const matrixBContainer =
    document.getElementById("matrixBContainer");


// ==================================================
// CREATE DIMENSION OPTIONS
// ==================================================

function createDimensionOptions(select) {

    for (let i = 1; i <= 10; i++) {

        const option = document.createElement("option");

        option.value = i;
        option.textContent = i;

        select.appendChild(option);
    }
}


// ==================================================
// INITIAL SETUP
// ==================================================

createDimensionOptions(rowsA);
createDimensionOptions(colsA);
createDimensionOptions(rowsB);
createDimensionOptions(colsB);

rowsA.value = 2;
colsA.value = 2;

rowsB.value = 2;
colsB.value = 2;


// ==================================================
// CREATE MATRIX GRID
// ==================================================

function createMatrixGrid(rows, cols, grid, matrixName) {

    grid.innerHTML = "";

    grid.style.gridTemplateColumns =
        `repeat(${cols}, 65px)`;

    for (let i = 0; i < rows; i++) {

        for (let j = 0; j < cols; j++) {

            const input =
                document.createElement("input");

            input.type = "number";
            input.className = "matrix-input";
            input.id = `${matrixName}_${i}_${j}`;
            input.placeholder = "0";


            // Keyboard navigation

            input.addEventListener(
                "keydown",
                function (event) {

                    const allInputs =
                        Array.from(
                            grid.querySelectorAll(
                                ".matrix-input"
                            )
                        );

                    const currentIndex =
                        allInputs.indexOf(input);

                    const currentRow =
                        Math.floor(
                            currentIndex / cols
                        );

                    const currentCol =
                        currentIndex % cols;


                    // Enter

                    if (event.key === "Enter") {

                        event.preventDefault();

                        const nextIndex =
                            currentIndex + 1;

                        if (
                            nextIndex <
                            allInputs.length
                        ) {

                            allInputs[
                                nextIndex
                            ].focus();

                        }
                        else if (
                            matrixName === "A" &&
                            operationRequiresMatrixB()
                        ) {

                            const firstBInput =
                                matrixBGrid.querySelector(
                                    ".matrix-input"
                                );

                            if (firstBInput) {
                                firstBInput.focus();
                            }
                        }

                        return;
                    }


                    // Left

                    if (
                        event.key === "ArrowLeft" &&
                        currentCol > 0
                    ) {

                        event.preventDefault();

                        allInputs[
                            currentIndex - 1
                        ].focus();

                        return;
                    }


                    // Right

                    if (
                        event.key === "ArrowRight" &&
                        currentCol < cols - 1
                    ) {

                        event.preventDefault();

                        allInputs[
                            currentIndex + 1
                        ].focus();

                        return;
                    }


                    // Up

                    if (
                        event.key === "ArrowUp" &&
                        currentRow > 0
                    ) {

                        event.preventDefault();

                        allInputs[
                            currentIndex - cols
                        ].focus();

                        return;
                    }


                    // Down

                    if (
                        event.key === "ArrowDown" &&
                        currentRow < rows - 1
                    ) {

                        event.preventDefault();

                        allInputs[
                            currentIndex + cols
                        ].focus();
                    }
                }
            );

            grid.appendChild(input);
        }
    }
}


// ==================================================
// OPERATION CHECKS
// ==================================================

function operationRequiresMatrixB() {

    return (
        operation.value === "addition" ||
        operation.value === "subtraction" ||
        operation.value === "multiplication"
    );
}


function operationRequiresSquareMatrix() {

    return (
        operation.value === "determinant" ||
        operation.value === "inverse"
    );
}


// ==================================================
// UPDATE MATRICES
// ==================================================

function updateMatrixA() {

    createMatrixGrid(
        Number(rowsA.value),
        Number(colsA.value),
        matrixAGrid,
        "A"
    );
}


function updateMatrixB() {

    createMatrixGrid(
        Number(rowsB.value),
        Number(colsB.value),
        matrixBGrid,
        "B"
    );
}


// ==================================================
// DIMENSION CHANGE
// ==================================================

rowsA.addEventListener(
    "change",
    updateMatrixA
);

colsA.addEventListener(
    "change",
    updateMatrixA
);

rowsB.addEventListener(
    "change",
    updateMatrixB
);

colsB.addEventListener(
    "change",
    updateMatrixB
);


// ==================================================
// OPERATION CHANGE
// ==================================================

operation.addEventListener(
    "change",
    function () {

        if (operationRequiresMatrixB()) {

            matrixBContainer.style.display =
                "block";

        }
        else {

            matrixBContainer.style.display =
                "none";
        }
    }
);


// ==================================================
// INITIAL MATRICES
// ==================================================

updateMatrixA();
updateMatrixB();


// ==================================================
// READ MATRIX
// ==================================================

function getMatrix(
    rowsSelect,
    colsSelect,
    matrixName
) {

    const rows =
        Number(rowsSelect.value);

    const cols =
        Number(colsSelect.value);

    const matrix = [];

    for (let i = 0; i < rows; i++) {

        const row = [];

        for (let j = 0; j < cols; j++) {

            const input =
                document.getElementById(
                    `${matrixName}_${i}_${j}`
                );

            if (
                !input ||
                input.value === ""
            ) {

                return null;
            }

            row.push(
                Number(input.value)
            );
        }

        matrix.push(row);
    }

    return matrix;
}


function getMatrixA() {

    return getMatrix(
        rowsA,
        colsA,
        "A"
    );
}


function getMatrixB() {

    return getMatrix(
        rowsB,
        colsB,
        "B"
    );
}


// ==================================================
// CALCULATE
// ==================================================

function calculate() {

    const selectedOperation =
        operation.value;


    // Read Matrix A

    const matrixA =
        getMatrixA();

    if (matrixA === null) {

        alert(
            "Please enter all elements of Matrix A."
        );

        return;
    }


    const aRows =
        Number(rowsA.value);

    const aCols =
        Number(colsA.value);


    // Validate square matrix

    if (operationRequiresSquareMatrix()) {

        if (aRows !== aCols) {

            alert(
                "Matrix A must be a square matrix for " +
                selectedOperation + "."
            );

            return;
        }
    }


    // Create request

    const requestData = {

        operation:
            selectedOperation,

        matrixA:
            matrixA
    };


    // Operations requiring Matrix B

    if (operationRequiresMatrixB()) {

        const matrixB =
            getMatrixB();

        if (matrixB === null) {

            alert(
                "Please enter all elements of Matrix B."
            );

            return;
        }


        const bRows =
            Number(rowsB.value);

        const bCols =
            Number(colsB.value);


        // Addition and subtraction

        if (
            selectedOperation === "addition" ||
            selectedOperation === "subtraction"
        ) {

            if (
                aRows !== bRows ||
                aCols !== bCols
            ) {

                alert(
                    "For " +
                    selectedOperation +
                    ", Matrix A and Matrix B must have the same dimensions."
                );

                return;
            }
        }


        // Multiplication

        if (
            selectedOperation === "multiplication"
        ) {

            if (aCols !== bRows) {

                alert(
                    "For multiplication, " +
                    "the columns of Matrix A must be equal " +
                    "to the rows of Matrix B."
                );

                return;
            }
        }


        requestData.matrixB =
            matrixB;
    }


    // ==================================================
    // SEND DATA TO C++ BACKEND
    // ==================================================

    fetch(
        "/calculate",
        {
            method: "POST",

            headers: {
                "Content-Type":
                    "application/json"
            },

            body:
                JSON.stringify(
                    requestData
                )
        }
    )

    .then(response => {

        if (!response.ok) {

            throw new Error(
                "Server returned an error."
            );
        }

        return response.json();
    })

    .then(data => {

        // Backend error

        if (!data.success) {

            alert(
                "Error: " +
                data.error
            );

            return;
        }


        // Save result for result.html

        const resultPageData = {

            operation:
                selectedOperation,

            matrixA:
                matrixA,

            result:
                data.result
        };


        if (operationRequiresMatrixB()) {

            resultPageData.matrixB =
                requestData.matrixB;
        }


        sessionStorage.setItem(
            "matrixResult",
            JSON.stringify(
                resultPageData
            )
        );


        // Open result page

        window.location.href =
            "result.html";
    })

    .catch(error => {

        alert(
            "Could not connect to C++ backend.\n\n" +
            "Make sure server.exe is running.\n\n" +
            error.message
        );
    });
}


// ==================================================
// CLEAR MATRIX A
// ==================================================

function clearMatrixA() {

    updateMatrixA();

    const firstAInput =
        matrixAGrid.querySelector(
            ".matrix-input"
        );

    if (firstAInput) {
        firstAInput.focus();
    }
}


// ==================================================
// CLEAR MATRIX B
// ==================================================

function clearMatrixB() {

    updateMatrixB();

    const firstBInput =
        matrixBGrid.querySelector(
            ".matrix-input"
        );

    if (firstBInput) {
        firstBInput.focus();
    }
}