using SharpDX.D3DCompiler;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Graphics
{
	class PixelShader : Shader, IDisposable
	{
		SharpDX.Direct3D11.PixelShader shader;

		public PixelShader(string filename)
		{
			compilationResult = ShaderBytecode.CompileFromFile(filename, "main", "ps_4_0", ShaderFlags.Debug);

			shader = new SharpDX.Direct3D11.PixelShader(Renderer.Instance.Device3D, compilationResult.Bytecode);
		}

		private CompilationResult compilationResult;

		public void Dispose()
		{
			compilationResult.Dispose();
			shader.Dispose();
		}
	}
}
