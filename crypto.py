import (
    "github.com/cosmos/cosmos-sdk/baseapp"
    "github.com/cosmos/cosmos-sdk/client"
    "github.com/cosmos/cosmos-sdk/codec"
    "github.com/cosmos/cosmos-sdk/server"
    "github.com/cosmos/cosmos-sdk/simapp"
    "github.com/cosmos/cosmos-sdk/x/auth"
    "github.com/cosmos/cosmos-sdk/x/bank"
    "github.com/cosmos/cosmos-sdk/x/staking"
    "github.com/spf13/cobra"
)

func main() {
    cdc := codec.New()
    app := simapp.NewSimApp(
        baseapp.NewBaseApp("cosmos-sdk", nil, nil, nil, baseapp.SetPruning("syncable")),
        cdc,
        nil,
        true,
    )

    rootCmd := &cobra.Command{
        Use:   "cosmosd",
        Short: "Cosmos Daemon (server)",
        RunE: func(cmd *cobra.Command, args []string) error {
            return server.StartCmd(cmd, app)
        },
    }

    rootCmd.AddCommand(client.LineBreak)
    authCmd := auth.Cmd(nil)
    rootCmd.AddCommand(authCmd)

    bankCmd := bank.Cmd(nil)
    rootCmd.AddCommand(bankCmd)

    stakingCmd := staking.Cmd(nil)
    rootCmd.AddCommand(stakingCmd)

    if err := rootCmd.Execute(); err != nil {
        panic(err)
    }
}
