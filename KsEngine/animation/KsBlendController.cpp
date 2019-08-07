
using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using System.Collections.ObjectModel;

namespace Airy
{

    /// <summary>
    /// An IAnimationController that blends an arbitrary number of other controllers together
    /// using the formula M_final = sum(weight_i * M_i)
    /// </summary>
    public sealed class KsBlendController : GameComponent, IAnimationController
    {

        /// <summary>
        /// Creates a new MultiBlendController
        /// </summary>
        /// <param name="game">The game.</param>
        public KsBlendController(Game game) : base(game) 
        {
            game.Components.Add(this);
            controllerDict = new Dictionary<IAnimationController, float>();

        }

        private Dictionary<IAnimationController, float> controllerDict;
  

        #region IAnimationController Members

        /// <summary>
        /// Gets the current bone transform.
        /// </summary>
        /// <param name="pose">The pose.</param>
        /// <returns>The current transform of the bone.</returns>
        public Matrix GetCurrentBoneTransform(KsBonePose pose)
        {
            if (controllerDict.Count == 0)
            {
                return pose.DefaultTransform;
            }
            Matrix transform = new Matrix();
            Matrix m;
            foreach (KeyValuePair<IAnimationController, float> k in controllerDict)
            {
                if (k.Key.ContainsAnimationTrack(pose))
                {
                    m = k.Key.GetCurrentBoneTransform(pose);
                    transform += k.Value * m;
                }
                else
                {
                    transform += k.Value * pose.DefaultTransform;
                }
            }
            return transform;
        }

		/// <summary>
        /// Gets the current bone transform.
        /// </summary>
        /// <param name="pose">The pose.</param>
        /// <returns>The current transform of the bone.</returns>
        public Matrix GetCurrentBoneTransform(KsJoint pose)
        {
			return pose.DefaultTransform;
        }

        /// <summary>
        /// Gets a dictionary that maps controllers to their weights.
        /// </summary>
        public Dictionary<IAnimationController, float> ControllerWeightDictionary
        {
            get { return controllerDict; }
        }

        /// <summary>
        /// Returns true if the controller can affect the bone.
        /// </summary>
        /// <param name="pose">The bone.</param>
        /// <returns>True if the controller can affect the bone.</returns>
        public bool ContainsAnimationTrack(KsBonePose pose)
        {
            return true;
        }


        private void OnAnimationTracksChanged(EventArgs e)
        {
            if (AnimationTracksChanged != null)
                AnimationTracksChanged(this, e);
        }

        /// <summary>
        /// Fired when different bones can be affected by the controller.
        /// </summary>
        public event EventHandler AnimationTracksChanged;

        #endregion

        #region IAnimationController Members




        #endregion
    }
}
