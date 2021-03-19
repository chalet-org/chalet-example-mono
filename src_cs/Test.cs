using System;
using System.Runtime.CompilerServices;

class MonoEmbed
{
	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	extern static string gimme();

	static int Main()
	{
		var result = gimme();
		System.Console.WriteLine(result);
		if (result.Equals("All your monos are belong to us!"))
			return 0;
		return 100;
	}
}