using System.ComponentModel;
using System.Collections.Generic;

namespace ScriptEditor
{
	//=============================================================
	// 検索用ディクショナリと表示用バインディングリストを持つ
	//	主に名前で検索し、リストボックスに表示する項目を扱う
	//=============================================================
	public interface IName
	{
		string GetName ();
	}

	public class BindingDictionary < T > where T : IName
	{
		private BindingList < T > BL_t = new BindingList < T > ();
		private Dictionary < string, T > DCT_t = new Dictionary < string, T > ();

		public void Add ( string name, T t )
		{
			BL_t.Add ( t );
			DCT_t.Add ( name, t );
		}

		public T Get ( string name )
		{
			//※ ジェネリックにおけるdefaultは対象の型の既定値を返す
			// 参照型はnull、数値型は0
			// 構造体はすべてのメンバーに対し0またはnull
			return DCT_t.TryGetValue ( name, out T t ) ? t : default ( T );
		}

		public void RemoveAt ( int index )
		{
			if ( index < 0 || BL_t.Count <= index ) { return; }
			string name = BL_t [ index ].GetName ();
			BL_t.RemoveAt ( index );
			DCT_t.Remove ( name );
		}

		public void Remove ( string name )
		{
			BL_t.Remove ( DCT_t [ name ] );
			DCT_t.Remove ( name );
		}

		public void Clear ()
		{
			BL_t.Clear ();
			DCT_t.Clear ();
		}

		public BindingList < T > GetBindingList ()
		{
			return BL_t;
		}

		public void Insert ( string name, T t )
		{
			int i = BL_t.IndexOf ( t );
			BL_t.Insert ( i, t );
			DCT_t.Add ( name, t );
		}
	}
}
