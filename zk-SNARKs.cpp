# Generate blinding factors and commitments
ctx = secp.Context()
blind_factor_1 = ctx.randomize32()
blind_factor_2 = ctx.randomize32()
value = 1000  # Value to be committed

commit_1 = ctx.pedersen_commit(value, blind_factor_1)
commit_2 = ctx.pedersen_commit(0, blind_factor_2)  # Dummy commitment

# Range proof to ensure value is positive and within a range
rangeproof = ctx.rangeproof_sign(commit_1, blind_factor_1, value, '12345', 0, 64)

# Verify range proof
valid = ctx.rangeproof_verify(commit_1, rangeproof, '12345')

print(f"Range proof valid: {valid}")
