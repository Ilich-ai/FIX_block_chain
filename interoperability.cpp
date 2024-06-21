#include <libsnark/common/default_types/r1cs_gg_ppzksnark_pp.hpp>
#include <libsnark/gadgetlib1/gadgets/basic_gadgets.hpp>
#include <libsnark/gadgetlib1/protoboard.hpp>
#include <libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp>

using namespace libsnark;

int main() {
    // Initialize the curve parameters
    default_r1cs_gg_ppzksnark_pp::init_public_params();

    // Create the protoboard
    protoboard<Fr<default_r1cs_gg_ppzksnark_pp>> pb;

    // Define variables and constraints
    pb_variable<Fr<default_r1cs_gg_ppzksnark_pp>> x, y, result;
    x.allocate(pb, "x");
    y.allocate(pb, "y");
    result.allocate(pb, "result");
    pb.set_input_sizes(2);

    pb.add_r1cs_constraint(r1cs_constraint<Fr<default_r1cs_gg_ppzksnark_pp>>(x * y, 1, result), "x * y = result");

    // Set values for x and y
    pb.val(x) = 3;
    pb.val(y) = 4;
    pb.val(result) = 12;

    // Generate keypair
    auto keypair = r1cs_gg_ppzksnark_generator<default_r1cs_gg_ppzksnark_pp>(pb.get_constraint_system());

    // Create the proof
    auto proof = r1cs_gg_ppzksnark_prover(keypair.pk, pb.primary_input(), pb.auxiliary_input());

    // Verify the proof
    bool result = r1cs_gg_ppzksnark_verifier_strong_IC(keypair.vk, pb.primary_input(), proof);

    std::cout << "Verification result: " << result << std::endl;

    return 0;
}
