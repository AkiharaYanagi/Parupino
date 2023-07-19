using System.Windows.Forms;


namespace ScriptEditor
{
	//------------------------------------------
	//	コンペンドに対するサブフォームの基本クラス
	//------------------------------------------

	public class SubForm_Compend : EditorForm
	{
		//編集参照
		public EditCompend EditCompend { get; set; } = new EditCompend ();
		public void SetEditCompend ( EditCompend ec )
		{
			EditCompend = ec;
		}
	}
}
