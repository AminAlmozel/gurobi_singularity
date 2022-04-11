#include "gurobi_c++.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    GRBEnv* env = new GRBEnv();
    GRBModel model = GRBModel(*env);
    // Initializing variables
    int num_vars = 5;
    int dimensions = 2;
    double v_limits[2] = { 1000, 1000 };
    double* vlb = new double[num_vars]{ -GRB_INFINITY };
    double* vub = new double[num_vars]{ GRB_INFINITY };
    char* vtype = new char[num_vars]{ GRB_CONTINUOUS };

    for (int i = 0; i < num_vars; i++) {
        vtype[i] = GRB_CONTINUOUS;
        vlb[i] = -v_limits[i % dimensions];
        vub[i] = v_limits[i % dimensions];
    }
    GRBVar* v = model.addVars(vlb, vub, NULL, vtype, NULL, num_vars);
    // Initializing objective
    GRBQuadExpr obj;
    obj.clear();
    obj += (v[0] - 3) * (v[0] - 3);
    model.setObjective(obj, GRB_MINIMIZE);
    // Setting constraints
    model.addConstr(v[0] >= 1);

    // Optimizing
    model.set(GRB_IntParam_OutputFlag, 1);
    // Set a 2 second time limit
    model.set(GRB_DoubleParam_TimeLimit, 60);
    model.update();
    try {
        //model.set(GRB_IntParam_Presolve, 0);
        model.set(GRB_IntParam_NonConvex, 2);
        // Optimize
        model.update();
        //model.reset(0);
        model.optimize();
    }
    catch (GRBException e)
    {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    }
    catch (...)
    {
        cout << "Error during optimization" << endl;
    }
    cout << "Optimal value is: " << v[0].get(GRB_DoubleAttr_X) << endl;
    cout << "Ran code successfully" << endl;
    return 0;
}

