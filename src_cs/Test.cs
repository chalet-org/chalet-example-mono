using System;
using System.Runtime.CompilerServices;

class MonoEmbed
{
	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	extern static string gimme();

	static int Main()
	{
		System.Console.WriteLine("This is a C# message.");

		string result = gimme();
		System.Console.WriteLine(result);

		if (result.Equals("This is some C++ called from C#!"))
			return 0;

		return 1;
	}
}