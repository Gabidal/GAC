use "cstd.e"

$pattern (
	if (i:ID == "ldr")(
		if (i:(Parameters:(0:Flags)) & Flag:_Register_)(
			if (i:(Parameters:(1:Name)) == "0")(
				i:(Parameters:1) = i:(Parameters:0),
				i:ID = "^"
			)
		)
	)
)


func main()(
	int a = 0
	return a
)