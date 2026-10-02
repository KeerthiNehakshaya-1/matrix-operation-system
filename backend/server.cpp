#define _WIN32_WINNT 0x0A00

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "httplib.h"
#include "json.hpp"
#include "matrix.h"

using namespace std;
using json = nlohmann::json;


// ==================================================
// CREATE MATRIX FROM JSON
// ==================================================

Matrix createMatrix(const json& data)
{
    int rows = data.size();
    int cols = data[0].size();

    Matrix M;

    M.setDimensions(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M.setValue(
                i,
                j,
                data[i][j].get<double>()
            );
        }
    }

    return M;
}


// ==================================================
// CONVERT MATRIX TO JSON
// ==================================================

json matrixToJson(Matrix& M)
{
    json result = json::array();

    for (int i = 0; i < M.getRows(); i++)
    {
        json row = json::array();

        for (int j = 0; j < M.getCols(); j++)
        {
            row.push_back(
                M.getValue(i, j)
            );
        }

        result.push_back(row);
    }

    return result;
}


// ==================================================
// MAIN
// ==================================================

int main()
{
    httplib::Server server;
        // Serve frontend files
    if (!server.set_mount_point("/", "../frontend"))
    {
        cerr << "Failed to mount frontend folder." << endl;
        return 1;
    }


    // ==========================================
    // CORS
    // ==========================================

    server.set_pre_routing_handler(
        [](const httplib::Request& req,
           httplib::Response& res)
        {
            res.set_header(
                "Access-Control-Allow-Origin",
                "*"
            );

            res.set_header(
                "Access-Control-Allow-Headers",
                "Content-Type"
            );

            res.set_header(
                "Access-Control-Allow-Methods",
                "GET, POST, OPTIONS"
            );

            if (req.method == "OPTIONS")
            {
                res.status = 200;

                return httplib::Server::HandlerResponse::Handled;
            }

            return httplib::Server::HandlerResponse::Unhandled;
        }
    );


    // ==========================================
    // TEST ROUTE
    // ==========================================



    // ==========================================
    // CALCULATE
    // ==========================================

    server.Post(
        "/calculate",
        [](const httplib::Request& req,
           httplib::Response& res)
        {
            try
            {
                json request =
                    json::parse(req.body);


                string operation =
                    request["operation"].get<string>();


                json matrixAData =
                    request["matrixA"];


                Matrix A =
                    createMatrix(matrixAData);


                json response;


                // ==================================
                // ADDITION
                // ==================================

                if (operation == "addition")
                {
                    json matrixBData =
                        request["matrixB"];

                    Matrix B =
                        createMatrix(matrixBData);


                    if (
                        A.getRows() != B.getRows() ||
                        A.getCols() != B.getCols()
                    )
                    {
                        response["success"] = false;

                        response["error"] =
                            "Matrix addition requires both matrices to have the same dimensions.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    Matrix C =
                        A.addition(B);


                    response["success"] = true;

                    response["result"] =
                        matrixToJson(C);
                }


                // ==================================
                // SUBTRACTION
                // ==================================

                else if (operation == "subtraction")
                {
                    json matrixBData =
                        request["matrixB"];

                    Matrix B =
                        createMatrix(matrixBData);


                    if (
                        A.getRows() != B.getRows() ||
                        A.getCols() != B.getCols()
                    )
                    {
                        response["success"] = false;

                        response["error"] =
                            "Matrix subtraction requires both matrices to have the same dimensions.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    Matrix C =
                        A.subtraction(B);


                    response["success"] = true;

                    response["result"] =
                        matrixToJson(C);
                }


                // ==================================
                // MULTIPLICATION
                // ==================================

                else if (operation == "multiplication")
                {
                    json matrixBData =
                        request["matrixB"];

                    Matrix B =
                        createMatrix(matrixBData);


                    if (
                        A.getCols() != B.getRows()
                    )
                    {
                        response["success"] = false;

                        response["error"] =
                            "Matrix multiplication requires columns of Matrix A to equal rows of Matrix B.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    Matrix C =
                        A.multiplication(B);


                    response["success"] = true;

                    response["result"] =
                        matrixToJson(C);
                }


                // ==================================
                // TRANSPOSE
                // ==================================

                else if (operation == "transpose")
                {
                    Matrix C =
                        A.transpose();


                    response["success"] = true;

                    response["result"] =
                        matrixToJson(C);
                }


                // ==================================
                // DETERMINANT
                // ==================================

                else if (operation == "determinant")
                {
                    if (
                        A.getRows() != A.getCols()
                    )
                    {
                        response["success"] = false;

                        response["error"] =
                            "Determinant can only be calculated for a square matrix.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    double det =
                        A.determinant();


                    response["success"] = true;

                    response["result"] =
                        det;
                }


                // ==================================
                // INVERSE
                // ==================================

                else if (operation == "inverse")
                {
                    if (
                        A.getRows() != A.getCols()
                    )
                    {
                        response["success"] = false;

                        response["error"] =
                            "Inverse can only be calculated for a square matrix.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    double det =
                        A.determinant();


                    if (fabs(det) < 1e-10)
                    {
                        response["success"] = false;

                        response["error"] =
                            "Matrix A is singular. The inverse does not exist.";

                        res.set_content(
                            response.dump(),
                            "application/json"
                        );

                        return;
                    }


                    Matrix C =
                        A.inverse();


                    response["success"] = true;

                    response["result"] =
                        matrixToJson(C);
                }


                // ==================================
                // INVALID OPERATION
                // ==================================

                else
                {
                    response["success"] = false;

                    response["error"] =
                        "Invalid matrix operation.";
                }


                res.set_content(
                    response.dump(),
                    "application/json"
                );
            }


            // ======================================
            // ERROR HANDLING
            // ======================================

            catch (const exception& e)
            {
                json errorResponse;

                errorResponse["success"] = false;

                errorResponse["error"] =
                    e.what();

                res.status = 400;

                res.set_content(
                    errorResponse.dump(),
                    "application/json"
                );
            }
        }
    );


    // ==========================================
    // START SERVER
    // ==========================================

    cout << "=====================================\n";
    cout << "      MATRIX C++ BACKEND\n";
    cout << "=====================================\n";
    cout << "Starting server...\n";
    cout << "=====================================\n";


    // Get PORT from hosting service

    const char* portEnvironment =
        getenv("PORT");


    int port = 8080;


    if (portEnvironment != nullptr)
    {
        port =
            atoi(portEnvironment);
    }


    cout << "Server listening on port: "
         << port
         << "\n";

    cout << "=====================================\n";


    // Listen on all network interfaces

    server.listen(
        "0.0.0.0",
        port
    );


    return 0;
}